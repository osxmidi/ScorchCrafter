# Scorchcrafter amp sim Linux 64 bit vst and lv2


ScorchCrafter Amp Sim (short demo at https://soundcloud.com/aaabii/test)

Quad core (or more) systems recommended.

Does not include cabinets/IR.

Some possible IR loaders https://github.com/osxmidi/KlangFalter and http://lsp-plug.in/ (Impulsantworten)

-----

(GPL https://sourceforge.net/p/scorchcrafter/wiki/Home/) 

Uses a modified Distrho dpf version (https://github.com/DISTRHO)

To make

Pre installed libraries needed, sudo apt-get install libx11-dev and sudo apt-get install libgl1-mesa-dev

Unzip dpf.zip

change into the dgl folder and run make

change into the dpf/utils folder and run

python ./png2rgba.py DistrhoArtworkScorch (your path to /ScorchcrafterGUI/plugins/Scorch/artwork)

(requires the Python Imaging Library, sudo apt-get install python-pil)

Move DistrhoArtworkScorch.cpp and DistrhoArtworkScorch.hpp to /ScorchcrafterGUI/plugins/Scorch

change into /ScorchcrafterGUI/plugins/Scorch/Guitar_Amplifier_Heads and run ./compile.sh to make scorchcrafter.o (chmod +x compile.sh might be needed)

change into /ScorchcrafterGUI/plugins/Scorch and run make

Binaries appear in the /ScorchcrafterGUI/bin folder

oversample.zip is for the oversampling version


