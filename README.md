# Scorchcrafter amp sim Linux 64 bit vst

Quad core (or more) systems recommended.

Does not include cabinets.

Some possible IR Loaders/IR cabinets, Reaper's ReaVerb, http://distrho.sourceforge.net/ports (Klangfalter, To use the Klangfalter plugin, click on "no file loaded" to load a IR file) or https://github.com/osxmidi/KlangFalter, http://lsp-plug.in/ (Impulsantworten), http://flos-audio-plugins.eu/

-----

(GPL https://sourceforge.net/p/scorchcrafter/wiki/Home/) 

Uses a modified Distrho dpf version (https://github.com/DISTRHO)

To make

Unzip dpf.zip

change into the dgl folder and run make

change into the dpf/utils folder and run

python ./png2rgba.py DistrhoArtworkScorch (pathto /ScorchcrafterGUI/plugins/Scorch/artwork)

Move DistrhoArtworkScorch.cpp and DistrhoArtworkScorch.hpp to /ScorchcrafterGUI/plugins/Scorch

change into /ScorchcrafterGUI/plugins/Scorch/Guitar_Amplifier_Heads folder and run ./compile.sh to make scorchcrafter.o (chmod +x compile.sh might be needed)

change into /ScorchcrafterGUI/plugins/Scorch 

run make

Binaries appear in the /ScorchcrafterGUI/bin folder

oversample.zip is for the oversampling version


