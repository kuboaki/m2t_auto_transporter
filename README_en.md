[English](README_en.md) | [日本語](README.md)

# EV3RT programs generated from model diagrams using Astah m2t plugin

This repository provides a sample program for Mindstorms EV3 running on TOPPERS/EV3RT, generated from UML model diagrams using Astah Professional with m2t plugin.

## Motivation

Even if you use UML class diagrams and state machine diagrams as software design documents, when it comes to implementation, you often end up writing code in a way that does not correspond to the elements and structure of those diagrams. This situation tends to be especially true in the case of handwritten code.

To avoid this problem, stop thinking "how should I write this?", when implementing it.
Instead, determine the "rules for mapping from model to codes" before designing. Designers design on the assumption that implementers will use the rules. The implementer implements according to the rules.

To avoid this, when you get to implementation, stop thinking, "How shall I write it?" . Instead, decide at the design stage how the code should be written if the diagram looks like this, and then draw the model diagram on the assumption that you will use that way of writing.

In Model-Driven Development (MDD), this "rules for mapping from model to codes" is called "translation rules". MDD usually aims to automate the translation process, but manual translation is also acceptable. However, in order to actually create rules and use it to translation, it would be easier to tryng "code generation," that translates from the model to the codes.

Therefore, in this repository, we decided to introduce an example of automatic translation from model diagrams created by a modeling tool into source code.

## Assumptions

The sample handled in this repository is an "Auto Transporter" that transports cargo. We originally built this robot using a LEGO Mindsorms EV3 kit (hereafter simply called EV3).
Here, instead of using the actual EV3, we will experiment using the simulation environment provided by the TOPPERS Hakoniwa Project.

We will use "Astah* Professional" developed and sold by Change Vision Co., Ltd. for modeling. For the tranlation process, Astah's "m2t" plugin will be used.


* LEGO Mindstorms EV3(LEGO Group)
* hakoniwa-single_robot(TOPPERS Hakoniwa WG): v1.3.1
* TOPPERS/EV3RT(TOPPERS Project) 1.1-release
* Astah* Professional(Change Vision Inc.) 8.5.0
* m2t plugin(Hosoai) 1.5.2

## Handwritten system demo
First, it's good to know what your target system is.
I created a class diagram and a state machine diagram using UML, and created the code by hand with reference to the diagram.

1. Wait at the waiting station for your cargo to be loaded
1. When the bumper is pushed, it is regarded as an instruction to start driving, and transportation is started.
1. Transport along the route
1. Stop when the delivery station is detected
1. Wait for your cargo to be unloaded
1. When the bumper is pushed, it is regarded as an instruction to start driving and forwarding is started.
1. Stop when the garage wall is detected

We will introduce a video of the actual machine (actual EV3 robot) version and a Hakoniwa (a simulation of a similar one in a virtual environment) version. Behavior is slightly different in the details, but please it wiill be ingnored.

* Demo of auto transpoting system created by hand (actual machine)

Click the thumbnail below to play the video.
Without pushing the bumper to start. and there is the wall of the garage is in front.

[![auto_transportor(EV3-sample04-02)](http://img.youtube.com/vi/uvHd9yemniY/hqdefault.jpg)](https://youtu.be/uvHd9yemniY)

* Demo of auto transpoting system createc by hand (hakoniwa)

Click the thumbnail below to play the video.

[![auto_transportor(hakoniwa-demo)](http://img.youtube.com/vi/eq0Dnm76bAs/hqdefault.jpg)](https://youtu.be/eq0Dnm76bAs)

NOTE: After here, it is still under construction.
