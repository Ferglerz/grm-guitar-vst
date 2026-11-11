// How much of each audio block the plugin takes with several guitars playing their rolls (average, 99th
// percentile, worst), at 48 kHz with 256-sample blocks.
// Usage: plugin_cpu_test [guitars]
#include <algorithm>
#include <chrono>
#include <cstdio>
#include <cstdlib>
#include <thread>
#include <vector>

#include <juce_audio_processors/juce_audio_processors.h>

#include "../plugin/PluginProcessor.h"

int main(int argc, char** argv) {
    juce::ScopedJuceInitialiser_GUI init;
    const int guitars = argc > 1 ? std::atoi(argv[1]) : 4;
    const double sr = 48000.0;
    const int block = 256;
    std::unique_ptr<juce::AudioProcessor> plugin(createPluginFilter());
    auto* g = dynamic_cast<GRMGuitarProcessor*>(plugin.get());
    plugin->setPlayConfigDetails(0, 2, sr, block);
    plugin->prepareToPlay(sr, block);
    for (int k = 1; k < guitars; ++k) {
        g->addGuitar();
        g->setSong(grmg::Song::demo());
    }
    if (argc > 2 && juce::String(argv[2]) == "noroom")
        for (int k = 0; k < guitars; ++k) g->params.getParameter(GuitarTrack::paramId(k, "room_on"))->setValueNotifyingHost(0.0f);
    juce::AudioBuffer<float> buf(2, block);
    juce::MidiBuffer midi;
    for (int k = 0; k < 1500; ++k) {          // the networks of every guitar
        plugin->processBlock(buf, midi);
        std::this_thread::sleep_for(std::chrono::milliseconds(4));
    }
    g->setInternalPlaying(true);
    std::vector<double> t;
    for (int k = 0; k < (int) (20 * sr / block); ++k) {
        const auto a = std::chrono::steady_clock::now();
        plugin->processBlock(buf, midi);
        t.push_back(std::chrono::duration<double>(std::chrono::steady_clock::now() - a).count());
    }
    int shown = 0;
    for (size_t k = 0; k < t.size() && shown < 12; ++k)
        if (t[k] > 0.4 * block / sr) {
            std::printf("  block %zu (%.2f s): %.0f%%\n", k, k * block / sr, 100 * t[k] / (block / sr));
            ++shown;
        }
    std::sort(t.begin(), t.end());
    double mean = 0;
    for (double v : t) mean += v;
    mean /= (double) t.size();
    const double budget = block / sr;
    std::printf("%d guitars: mean %.1f%%  p99 %.1f%%  worst %.1f%% of a block\n", guitars, 100 * mean / budget,
                100 * t[(size_t) (0.99 * (double) t.size())] / budget, 100 * t.back() / budget);
    plugin->releaseResources();
    return 0;
}
