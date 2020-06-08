# Scorchcrafter amp sim Linux 64 bit vst

Quad core (or more) systems recommended.

Does not include cabinets/IR.

Some possible IR Loaders, Reaper's ReaVerb, http://distrho.sourceforge.net/ports (KlangFalter, To use the KlangFalter plugin, click on "no file loaded" to load a IR file) or https://github.com/osxmidi/KlangFalter, http://lsp-plug.in/ (Impulsantworten)

-----

(GPL https://sourceforge.net/p/scorchcrafter/wiki/Home/) 

Uses a modified Distrho dpf version (https://github.com/DISTRHO)

To make

Unzip dpf.zip

change into the dgl folder and run make

change into the dpf/utils folder and run

python ./png2rgba.py DistrhoArtworkScorch (pathto /ScorchcrafterGUI/plugins/Scorch/artwork)

(requires the Python Imaging Library, sudo apt-get install python-pil)

Move DistrhoArtworkScorch.cpp and DistrhoArtworkScorch.hpp to /ScorchcrafterGUI/plugins/Scorch

change into /ScorchcrafterGUI/plugins/Scorch/Guitar_Amplifier_Heads folder and run ./compile.sh to make scorchcrafter.o (chmod +x compile.sh might be needed)

change into /ScorchcrafterGUI/plugins/Scorch 

run make

Binaries appear in the /ScorchcrafterGUI/bin folder

See Scorch-make-lv2.zip for making the lv2 version.

oversample.zip is for the oversampling version


