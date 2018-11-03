# IsingTown

A map generator based on thermodynamics Ising model

Could be used to generate medieval towns, cities, etc

## Idea

■=house

□=road

Energy=minus # of pairs of houses which can be connected by a path shorter than maxD

The metropolis algorithm:
- For each step, randomly select a block and change its color. Calculate the energy change ΔE
- if ΔE<0 accept the change
- if ΔE>0, there is a probability of exp(-β*ΔE) that the change would be accepted, otherwise rewind back
- iterator over and over...

It has been proven that after some iterations the probability distribution of the system becomes a Boltzman distribution. Which means each possible configuration of the system with energy E emerges with a probability propotional to exp(-βE)

- If β was too high, which means only the configuration with the most energy have a significent probability to exist. So the system collapsed into a perfect crystalline but lifeless state.
- If β was almostly zero, each configuration have almost equal possibility to emergy. Unfortunately, most of them are totally random pixels. Statistical mechanically speaking, the macro state which has the most # of micro states (entropy) dorminates.
- For a proper β, neither Energy nor Entropy prevails. The system exhibits a interesting balance between order and chaos. That's what we want.

Feel free to tweak the energy function and make fun maps!

![此处为图片加载失败时显示的文字](https://github.com/fangzhangmnm/IsingTown/raw/master/微信截图_20181028003551.png)
![此处为图片加载失败时显示的文字](https://github.com/fangzhangmnm/IsingTown/raw/master/微信截图_20181028003331.png)
![此处为图片加载失败时显示的文字](https://github.com/fangzhangmnm/IsingTown/raw/master/微信截图_20181028003359.png)
![此处为图片加载失败时显示的文字](https://github.com/fangzhangmnm/IsingTown/raw/master/微信截图_20181028003435.png)
![此处为图片加载失败时显示的文字](https://github.com/fangzhangmnm/IsingTown/raw/master/微信截图_20181028003517.png)
