# Scorchcrafter amp sim Linux 64 bit


ScorchCrafter Amp Sim (short demo at https://soundcloud.com/aaabii/test)

Quad core (or more) systems recommended.

Does not include cabinets/IR.

Some possible IR loaders https://github.com/osxmidi/KlangFalter and http://lsp-plug.in/ (Impulsantworten)

-----

A JUCE based version is at https://github.com/osxmidi/ScorchCrafter-JUCE

(GPL https://sourceforge.net/p/scorchcrafter/wiki/Home/) 

Uses a modified Distrho dpf version (https://github.com/DISTRHO)

To make

Pre installed libraries needed, sudo apt-get install libx11-dev and sudo apt-get install libgl1-mesa-dev and sudo apt-get install python-pil (and sudo apt-get install lv2-dev for lv2)

change into the ScorchcrafterGUI folder

Unzip dpf.zip

chmod +x scorchmake

./scorchmake

Binaries appear in the /ScorchcrafterGUI/bin folder

For lv2 run ./makelv2 in the /ScorchcrafterGUI/bin folder (probably requires a chmod +x makelv2 and a chmod +x lvmake)

-------

To make manually

change into the ScorchcrafterGUI folder

change into the dpf/dgl folder and run make

change into the dpf/utils folder and run

python ./png2rgba.py DistrhoArtworkScorch (your path to /ScorchcrafterGUI/plugins/Scorch/artwork)

(requires the Python Imaging Library, sudo apt-get install python-pil)

Move DistrhoArtworkScorch.cpp and DistrhoArtworkScorch.hpp to /ScorchcrafterGUI/plugins/Scorch

change into /ScorchcrafterGUI/plugins/Scorch/Guitar_Amplifier_Heads and run ./compile.sh to make scorchcrafter.o (chmod +x compile.sh might be needed)

change into /ScorchcrafterGUI/plugins/Scorch and run make

Binaries appear in the /ScorchcrafterGUI/bin folder

For lv2 run ./makelv2 in the /ScorchcrafterGUI/bin folder (probably requires a chmod +x makelv2 and a chmod +x lvmake)

oversample.zip is optional and is for a oversampling version


