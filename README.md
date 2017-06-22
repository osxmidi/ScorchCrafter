# Scorchcrafter amp sim Linux 64 bit GUI 

(GPL https://sourceforge.net/p/scorchcrafter/wiki/Home/) 

Uses Distrho

To make

Unzip dpf.zip

change into the dgl folder and run make

change into the dpf/utils folder and run

python ./png2rgba.py DistrhoArtworkScorch pathto->ScorchcrafterGUI/plugins/Scorch/artwork

change into /ScorchcrafterGUI/plugins/Scorch/Guitar_Amplifier_Heads folder and run ./compile.sh to make scorchcrafter.o

change into /ScorchcrafterGUI/plugins/Scorch and move the scorchcrafter.o file to it

run make

Binaries appear in  /ScorchcrafterGUI/bin folder


