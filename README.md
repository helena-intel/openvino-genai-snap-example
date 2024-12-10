# Create a Snap for an OpenVINO GenAI application

This is a very basic example for building a snap for an OpenVINO GenAI C++ application. Tested on Ubuntu 24.04.

More information:
- https://snapcraft.io/
- https://ubuntu.com/tutorials/create-your-first-snap (highly recommended)

## About the example

The example consists of three files: `CMakeLists.txt` and `openvinodemo.cpp` that make up the sample application, and `snap/snapcraft.yaml` that describes how to build the snap. The 
demo application is trivially simple and just runs a few tokens of inference on an LLM. For a more interesting application, rename openvinodemo_chatbot.cpp to openvinodemo.cpp. This creates a chatbot demo. The chatbot demo doesn't work with all models - models need to have a compatible chat template to work (For example: Llama 3.1 and 3.2 Instruct models).

## Limitations

- This example currently only works for OpenVINO inference on CPU.
- The example can by default only access models that are in (a subdirectory of) the user's $HOME directory. See the _Allow other directories_ section to allow other specific directories. It is not possible to allow all paths.

## Prerequisites

On a recent Ubuntu, `snap` itself should be installed. Follow the [Create your first Snap](https://ubuntu.com/tutorials/create-your-first-snap#2-getting-started) tutorial if it isn't.

### Install and configure snapcraft and dependencies

```
sudo snap install --classic snapcraft
```

Install `lxd` and add your user to the `lxd` group:

```shell
sudo groupadd --force --system lxd
sudo usermod -a -G lxd $USER
newgrp lxd
sudo snap install lxd
sudo lxd init --auto
```

The [tutorial](https://ubuntu.com/tutorials/create-your-first-snap#3-building-a-snap-is-easy) says you may be asked about multipass. I never was, for me
`lxd` was used by default.

### Configure demo

Clone this repository and download and uncompress the OpenVINO GenAI archive. This example uses OpenVINO 2024.5. For other OpenVINO
versions, change CMakeLists.txt to match.

Step-by-step:

```shell
git clone https://github.com/helena-intel/openvino-genai-snap-example.git
cd openvino-genai-snap-example
curl -O https://storage.openvinotoolkit.org/repositories/openvino_genai/packages/2024.5/linux/openvino_genai_ubuntu24_2024.5.0.0_x86_64.tar.gz
tar zxf openvino_genai_ubuntu24_2024.5.0.0_x86_64.tar.gz
mv openvino_genai_ubuntu24_2024.5.0.0_x86_64 openvino_genai
```

## Build the snap

Run the following command in the `openvino-genai-snap-example` directory

```shell
snapcraft
```

If all goes well, this creates a file openvinodemo_0.1_amd64.snap in the current directory.

> [!NOTE]
> If you get errors about network connectivity, like _A network related operation failed in a context of no network access_, it may be related to Docker. Working around that is
> out of scope for this example. `sudo iptables -P FORWARD ACCEPT` could work. Otherwise a suggestion is to (temporarily) remove Docker and reboot the machine.

## Install the snap

The `--dangerous` flag is needed because the app isn't signed by the Snap Store.
See the [Create your first snap](https://ubuntu.com/tutorials/create-your-first-snap) tutorial (section 6 and 7).

```shell
sudo snap install --dangerous openvinodemo_0.1_amd64.snap
```

You can copy this snap to another machine, and install and run it there without configuring anything.

## Run the demo

```shell
openvinodemo modelpath
```

> [!NOTE]
> If you do not have an OpenVINO LLM on your computer, you can download one by installing huggingface-hub `pip install huggingface-hub` and downloading
> a model from the hub with `huggingface-cli download`. For example: `huggingface-cli download llmware/llama-3.2-1b-instruct-ov --local-dir llmware/llama-3.2-1b-instruct-ov`
> to download [Llama-3.2-1B-Instruct](https://huggingface.co/llmware/llama-3.2-1b-instruct-ov) from [LLMWare](https://llmware.ai)'s [model depot](https://huggingface.co/collections/llmware/model-depot-6686b50b55721c8734596172)


## Allow other directories

By default snap allows access to $HOME only. To allow other specific directories, for example `/data/models` you can run the following command on the system where you run the application:

```shell
sudo snap set system homedirs=/data/models
```

See [home outside of home](https://snapcraft.io/docs/home-outside-home) documentation and [forum thread](https://forum.snapcraft.io/t/home-directories-outside-of-home/19224/12).


## Troubleshooting

### Build the application locally

To build the application without the snap (for example to test if it works):

```
source openvino_genai/setupvars.sh
mkdir build && cd build
cmake ..
cmake --build . --config Release
cmake --install . --prefix "openvinodemo_install"
```

### Snapcraft debug environment

Run `snapcraft --debug` instead of just `snapcraft` to launch a shell in the build environment.

### Installing on a different Linux distribution

If you install the snap on a Linux distro without snap installed by default, you can install snapd with `sudo apt install snapd`. If you then get
connection refused errors, even after `systemctl start`, try this (from https://stackoverflow.com/questions/66008918/cannot-communicate-with-server-post-http-localhost-v2-snaps-discord-dial-uni):

```shell
sudo systemctl unmask snapd.service
sudo systemctl enable snapd.service
sudo systemctl start snapd.service
```

