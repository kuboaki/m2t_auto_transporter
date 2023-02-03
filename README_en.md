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

## Handwritten(manual coding) system demo

First, it's good to know what your target system is.
I created a class diagram and a state machine diagram using UML, and created the code by hand with reference to the diagram.

1. Wait at the waiting station for your cargo to be loaded
1. When the bumper is pushed, it is regarded as an instruction to start driving, and transportation is started.
1. Transport along the route
1. Stop when the delivery station is detected
1. Wait for your cargo to be unloaded
1. When the bumper is pushed, it is regarded as an instruction to start driving and forwarding is started.
1. Stop when the garage wall is detected

We will introduce a video of the actual machine (real EV3 robot) version and a Hakoniwa (a simulation of a similar one in a virtual environment) version. Behavior is slightly different in the details, but please it wiill be ingnored.

* Demo of auto transpoting system created by hand (actual machine)

Click the thumbnail below to play the video.
Without pushing the bumper to start. and there is the wall of the garage is in front.

[![auto_transportor(EV3-sample04-02)](http://img.youtube.com/vi/uvHd9yemniY/hqdefault.jpg)](https://youtu.be/uvHd9yemniY)

* Demo of auto transpoting system createc by hand (hakoniwa)

Click the thumbnail below to play the video.

[![auto_transportor(hakoniwa-demo)](http://img.youtube.com/vi/eq0Dnm76bAs/hqdefault.jpg)](https://youtu.be/eq0Dnm76bAs)

NOTE: After here, it is still under construction in English.

## Setup UML modeling tool and plugin

### Install Astah* Professional

"Astah* Professional" is a tool for UML modeling. Change Vision Co., Ltd. develops and sells this tool.
You can purchase it from the company's website. You can get an evaluation version and give it a try.

[Astah* Professional Website](https://astah.change-vision.com/en/product/astah-professional.html)


### Check your license (for faculty)


Change Vision Co., Ltd. provides faculty site licenses that can be used across departments for educational institutions such as universities and vocational schools. Check to see if your school has it.


[Astah* Academic Licensing](https://astah.net/pricing/academic/)

### Install m2t plugin

"m2t plug-in" is developed by Shintaro Hosoai (s-hosoai). The source code of the plugin is published on GitHub.
For how to get the m2t plugin and how to install it on Astah* Professional, please refer to the following page.

[m2t plugin (Change Vision)](https://astah.change-vision.com/ja/plugin/astahm2t.md-plugin.html)

[m2t - Model to Text (GitHub)](https://github.com/s-hosoai/astahm2t)

## How to use the sample program

### Location of the cloned repository

This repository fits into a workspace within the EV3RT's build environment.
In the environment for the actual machine (real EV3), you can build with the EV3RT build script as it is by arranging it in the workspace directory.

* Layout of the sample repository in the EV3RT environment for the actual machine (real EV3)

```shell
(Omit unimportant directories)
sdk
├── m2t_workspace
│   ├── m2t_auto_transporter
│   └── m2t_ev3rt_templates
└── workspace
```

### Notes for using "Hakoniwa"

Hakoniwa (hakoniwa-single_robot) assumes that its various scripts are placed in `sdk/workspace`.
Therefore, even if m2t_workspace is placed in a different location, the simulator script will not recognize it.

* In Hakoniwa, `m2t_workspace` cannot be placed side by side with `workspace`.


```shell
(Omit unimportant directories)
fnsdk
├── m2t_workspace
│   ├── m2t_auto_transporter (not recognize at here)
│   └── m2t_ev3rt_templates
└── workspace
```

For use in Hakoniwa, after placing this repository in `sdk`, copy the generated source code to your existing `workspace` directory.

* In Hakoniwa, copy codes in `m2t_auto_transporter` to `workspace `.

```shell
(Omit unimportant directories)
├── m2t_workspace
│   ├── m2t_auto_transporter (use for code generation)
│   └── m2t_ev3rt_templates
└── workspace
    ├── helloev3
    ├── m2t_auto_transporter (use for building application)
    └── trike
```

If you're writing code from your own UML model diagrams, you should follow the structure of this repository.
In other words, place the model diagram, source code, and generation template in your own project workspace, and copy the generated code to the `workspace`.


## See the model diagram for this sample

Let's open the sample model diagram provided by this repository with Astah*.
The model file is `m2t_workspace/models/m2t_auto_transporter.asta`.

NOTE: sorry, diagrams are in Japanese.

* Class diagram for the sysytem

![auto_transporter system's class diagram](images/class_diagram.png)

* Statemachine diagram of the transport method in the auto_transporter class

![auto_transporter::transport statemachine diagram](images/auto_transporter_transport_stm.png)

* Statemachine diagram of the runner method in the line_tracer class

![line_tracer::runner statemachine diagram](images/line_tracer_runner_stm.png)


### Tempate settings

After you have installed the m2t plugin on Astah*, open the "Tools" menu and you will find "m2t" item.

Templates for generating code provided by this repository can be found in the `m2t_workspace/m2t_ev3rt_templates/` directory.

When the sample model diagram is opened for the first time, this location has not been reflected in the settings.
Open "m2t > setting" and set it as follows (the path name will be different depending on your environment, so please read it accordingly).

![template settings for using m2t plugin](images/template_settings_jp.png)

### Code generation

After setting the template, let's generate the source code from the sample model diagram.

If you select "m2t > generate" from the "Tools" menu, the source code will be generated in the directory set in `Destination Path` in the template settings.


```shell
(Omit unimportant directories)
sdk/m2t_workspace
├── m2t_auto_transporter (destination directory for code generation)
│   ├── Makefile.inc
│   ├── app.c
│   ├── app.cfg
│   ├── app.h
│   ├── auto_transporter.c
│   ├── auto_transporter.h
│   ├── （以下略）
│   └── wall_detector.h
├── m2t_ev3rt_templates
│   └── (templates for code generation)
└── models
    └── m2t_auto_transporter.asta (model file for code generation)

```

### Edit app.cfg

Since the generation rules are still insufficient, the difference between the implementation environment of EV3 and Hakoniwa cannot be absorbed.
Edit `app.cfg` before building (if you only use one or the other, fix the template later).

#### For actual machine (real EV3 robot)

For those who build and run for actual machine (real EV3), please edit `app.cfg` as follows.

* Delete `INCLUDE("tecsgen.cfg");`

```C
INCLUDE("app_common.cfg");

#include "app.h"
#include "ev3.h"

DOMAIN(TDOM_APP) {
CRE_TSK( MAIN_TASK, { TA_NULL, 0, main_task,  MAIN_PRIORITY, STACK_SIZE, NULL } );
CRE_CYC( CYC0, { TA_STA, { TNFY_ACTTSK, MAIN_TASK }, 50U * 1000U, 1});
}

(omitted below)
```

#### For for Hakoniwa

For those who build and run for Hakoniwa, please edit `app.cfg` as follows.

* Delete `DOMAIN`

```C
INCLUDE("app_common.cfg");
INCLUDE("tecsgen.cfg");

#include "app.h"
#include "ev3.h"

CRE_TSK( MAIN_TASK, { TA_NULL, 0, main_task,  MAIN_PRIORITY, STACK_SIZE, NULL } );
CRE_CYC( CYC0, { TA_STA, { TNFY_ACTTSK, MAIN_TASK }, 50U * 1000U, 1});

(omitted below)
```

### Build and run

After configuration. You can build and run the program.

#### For actual machine (real EV3)

Build the `app` file using `make` command.

```shell
$ cd {EV3RT installed directory}/hrp3/sdk/m2t_workspace
$ make app=m2t_auto_transporter
$ ls -l app
-rwxr-xr-x  1 kuboaki  staff  101480  8 30 00:42 app
```

Once you have built the `app` file, follow the instructions on the TOPPERS/EV3RT page to transfer the program and try to run it.

How about. Did it work as expected?

Let's check if the behavior is the same as the state machine diagram of the `transport` method in the `auto_transporter` class.

#### For for Hakoniwa

First, don't forget to run the docker container on terminal A before building.

```shell
$ cd {hakoniwa-single_robot root directory}
$ bash run-proxy.bash m2t_auto_transporter
```

Next, on terminal B, copy the generated source code to `workspace`.

```shell
$ cd {parent directory of m2t_workspace directory}
$ cp -prf m2t_auto_transporter {hakoniwa-single_robot root directory}/sdk/workspace
$ cd {hakoniwa-single_robot root directory}
$ ls sdk/workspace/m2t_auto_transporter
drwxr-xr-x  35 kuboaki  staff    1120  8 30 01:39 m2t_auto_transporter
```

And then, on terminal B, build using the shell script for building.

```shell
$ cd {hakoniwa-single_robot root directory}
$ bash build-app.bash clean
$ bash build-app.bash m2t_auto_transporter
$ ls -l sdk/workspace/asp
-rwxr-xr-x  1 kuboaki  staff  101480  8 30 00:42 asp
```

On terminal C, start the simulation.

Note: the command line specifies the name of the Unity app.

```shell
$ cd {hakoniwa-single_robot root directory}
$ bash star-unity.bash auto-transporter2　# note: parameter is the Unity app name.
```

How about. Did it work as expected?

Let's check if the behavior is the same as the state machine diagram of the `transport` method in the `auto_transporter` class.


## Modify model behaviar

Let's change the model and see if the generated code changes.
For example, think about how you could do something like this:

* Change 1) If the cargo has not been unloaded at the delivery destination, the train will not depart.
* Change 2) If the vehicle departs without picking up the cargo at the waiting area, the vehicle will not stop at the delivery destination, but will pass through and proceed to the garage and stop.

Probably, aside from the details, you can do it by changing the `auto_transporter` state machine diagram.

## Mapping statemachine diagrams to code

The sample provided in this repository uses a behavior model in which one task (`main_task`) is repeatedly invoked by a cyclic handler (`cyc0`).
In addition, reading sensor values ​​is also done in the same task by calling the API of the sensor and making judgments based on the values ​​(however, the sampling cycle is constant before and after the handler activation interval).

* Cyclic handlers and tasks in this example

![Cyclic handlers and tasks in this example](images/cyclic_handler_and_main_task.png)

Instead, this method takes care not to create closed loops inside the program, as each sensor's value is read in each cycle of the cyclic handler.
This is because if there is a closed loop inside the program, the values ​​of other sensors cannot be obtained while in that loop.

Some people call this kind of design work, which decides the processing method at the time of implementation, the implementation method.
It's not often talked about outside the model-driven copmunity, but in order to reduce the separation between implementation and design, it's important to determine the implementation scheme at the beginning of the design process, and then model the structure and behavior.


Each element of the state machine diagram and the code correspond as follows.

* Mapping state machine diagrams to code

![mapping state machine diagrams to code](images/stm_to_code.png)

Whether an event is detected as a change point (edge) or as an evaluation of the value at the time of acquisition depends on the internal processing of the function assigned as the event.
The do activity process is called every cycle.
Here, the process that drives along the path is called every cycle to read the path (the lines on the course).

## How to create a production rule

When it comes to code generation, there is no almighty generation engine that does what you want.
Instead, we can prepare and use conversion rules that are convenient for us.
Rather than aiming for a method that works 100% of the time, it would be fine to decide on a method that works 80% of the time and treat the remaining 20% ​​as an exception (for example, use handwritten code instead of excluding it from the generation target).

To generate the code we want, we first patternize the code we are writing with a processing pattern and the parameters used in that processing.
Then parameterize it with elements that can be obtained from the model where different classes (or methods) differ.

For example, in the `m2t_auto_transporter.c` file, the generated code is:

```C
typedef enum _auto_transporter_state_t {
    ATST_PSEUDO_END_STATE,
    ATST_WAIT_FOR_LOADING,
    ATST_TRANSPORTING,
    ATST_WAIT_FOR_UNLOADING,
    ATST_WAIT_FOR_START,
    ATST_WAIT_FOR_RETURN,
    ATST_WAIT_FOR_PASSING_STATION,
    ATST_ARRIVED,
    ATST_RUNNING_TOWARD_GARAGE
} auto_transporter_state_t;
```

The C `enum` and `typedef` syntax is already provided.
Therefore, we will decide the name of the type to be defined by linking it to the class name.

That is, names like:

```C
{class name}_state_t
```

The list of state names used in the statemachine diagram can be obtained from the model diagram.
In the m2t plugin it is placed in `u.states`.
To convert this to the enumeration name used in the program, the following format should be considered.

```C
each state in all states:
    prefix_{(capitalized)state name}
```

First, let's iterate through each state until we get each state name.

To pick one from a list of state names, use Groovy's `for`, which the m2t plugin uses as a template engine.

```Groovy
<% for(st in u.states){%>\
${st.name}
<%}%>\
```

`<%` to `%>` enclose parts that are not intended for output.
`\` at the end of a line suppresses the output of newlines.

Now we can iterate over all states and refer to each state name by `st.name`.

Next is the prefix.
You could use the class name as is, but that would be too long.
Therefore, in the model diagram, each class has a short "alias" (this is using the function provided by Astah* Professional).
Then, convert this alias to uppercase using grooby's method and use it as a prefix.

```C
u.iclass.alias1.toUpperCase()
```

To get the information in the model diagram like this, use Astah* API.
You can find the API reference in Java Doc format in the API's user guide.

[astah* API user guide](https://members.change-vision.com/javadoc/astah-api/8_1_0/api/ja/doc/index.html)

Now that we have the prefix and the state name, we just need to format it.

```Groovy
<% if(u.statemachine){%>\
<% for(st in u.states){%>\
    ${u.iclass.alias1.toUpperCase()}ST_${st.name.toUpperCase()},
<%}%>\
<%}%>\
```

The whole thing is wrapped in `<% if(u.statemachine){%>\` followed by `<%}%>\`.
This code needs to be generated only for classes for which a statemachine diagram is provided (`u.statemachine` is true).

The actual template uses "collect" and "join" as well as helper methods.

```Groovy
<% if(u.statemachine){%>\
typedef enum _${u.name}_state_t {
    ${getStateName("PSEUDO_END_STATE")}, // add pseudo state
${u.states.collect({"    " + getStateName(it)}).join(',\n')}
} ${u.name}_state_t;
<%}%>\
```

Using similar steps, we can create a template for each part of the source code that we want, so that we can generate code that is roughly the same (and a little cleaner) than the code we write by hand. will be

## Tips

If you write `${u.properties}` in the template, you can list the information that the m2t plugin has acquired as properties. It will be helpful.


## References

* [LEGO Mindstorms EV3(Wikipedia)](https://ja.wikipedia.org/wiki/Lego_Mindstorms_EV3)
* [hakoniwa-single_robot(TOPPERS Hakoniwa WG)](https://github.com/toppers/hakoniwa-single_robot)
* [TOPPERS/EV3RT(TOPPERS Project)](https://dev.toppers.jp/trac_user/ev3pf/wiki/WhatsEV3RT)
