# OpenVINO GenAI chatbot snap - batteries included

See the [main README](../README.md) for info on how to build a snap for this basic application and how to install and run it.


## Changes

This example builds on the [chatbot](../chatbot) example. The name is changed to `openvinochat` and the following features are added:

- support for GPU inference
- model caching for faster model loading
- an additional app: `openvinochat.modeldownload`, which downloads a sample model.
- a smarter way to install openvino_genai in the snap: 


### GPU inference

For GPU inference, we modify the snapcraft.yaml to
- add the `opengl` plug
- add a `layout` section
- add an `opencl` part

We also add the necessary files to install to CMakeLists.txt: the OpenVINO GPU plugin, the libOpenCL files, and
cache.json. Finally, we modify openvinochat.cpp to add an extra command line parameter to specify the device (CPU or
GPU).


### Model caching

Model caching is enabled by adding a `pipeline_config` containing `ov::cache_dir` to `LLMPipeline` in openvinochat.cpp. This creates the
model cache on the first run; on subsequent runs the cache will be used for model loading, and model loading will be faster. 


### modeldownload app

We create an extra app, `openvinochat.modeldownload`, which downloads an example model. The app is defined in the `apps` section in snapcraft.yaml. 
Since this is just an example app, `openvinochat.modeldownload` downloads a hardcoded example model
from the Hugging Face hub ([Llama-3.2-1B-Instruct](https://huggingface.co/llmware/llama-3.2-1b-instruct-ov) from 
[LLMWare](https://llmware.ai)'s awesome [model depot](https://huggingface.co/collections/llmware/model-depot-6686b50b55721c8734596172)).
It stores the model in the current directory. 

This app makes it really easy to test the snap, or OpenVINO, on a computer where you do not have any LLMs yet.


### Installing OpenVINO GenAI

In the basic snaps we manually downloaded openvino_genai. That is the easiest method, and least likely to go wrong, but
manual steps are not great, and you have to duplicate or link the data in every application directory. In this example,
we download the openvino_genai archive automatically in a separate part in snapcraft.yaml. This download is cached, so
it will only be re-downloaded when needed (for example when you update the OpenVINO version or change the code in the
openvino_genai part in snapcraft.yaml.


## Installing the snap

Both GPU access and network connectivity require using a snapcraft plug: `opengl` for GPU, and `network` for network. To
enable these plugs, we add them to the snapcraft.yaml. If the application is installed through the snapcraft store, this
is enough. The plugs will be autoconnected, and GPU and network will automatically work. This is not the case when
testing locally after installing with `--dangerous` as we have been doing in the basic examples. There are two options:

  1. Install the snap with `sudo snap install --dangerous openvinochat_0.1_amd64.snap` as before and then run `sudo snap connect openvinochat:network` and `sudo snap connect openvinochat:opengl`
  2. Install the snap with `sudo snap install --devmode openvinochat_0.1_amd64.snap`. With `--devmode` the snap gets full access to system resources. See https://snapcraft.io/docs/install-modes.

The first method is the safer method. It runs the snap as intended, and you immediately notice any issues. You only have
to run `snap connect` once. Even after uninstalling and reinstalling the app, the connections remain enabled.

## Run the demo

To allow GPU inference, the `openvinochat` app now takes to command line parameters: `model_path` and `device`. To allow running on GPU,
the system must have an Intel integrated or discrete GPU.

Example:

```
openvinochat.modeldownload
openvinochat llmware-llama-3.2-1b-instruct-ov CPU
```
