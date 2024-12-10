// Copyright (C) 2023-2024 Intel Corporation
// SPDX-License-Identifier: Apache-2.0
//
// Modified from https://github.com/openvinotoolkit/openvino.genai/tree/master/samples/cpp/chat_sample
// OpenVINO chat_sample WITHOUT HISTORY between questions
//
// Usage: openvinodemo /path/to/model

#include "openvino/genai/llm_pipeline.hpp"

std::string start_message = " <|start_header_id|>system<|end_header_id|>\n\n You are a helpful, respectful and honest assistant. Always answer as helpfully as possible, while being safe.  Your answers should not include any harmful, unethical, racist, sexist, toxic, dangerous, or illegal content. Please ensure that your responses are socially unbiased and positive in nature. Make sure that code is concise and correct.  If a question does not make any sense or is not factually coherent, explain why instead of answering something not correct. If you don't know the answer to a question, please don't share false information.<|eot_id|>";

int main(int argc, char* argv[]) try {
    if (2 != argc) {
        throw std::runtime_error(std::string{"Usage: "} + argv[0] + " <MODEL_DIR>");
    }
    std::string prompt; 
    std::string models_path = argv[1];
    std::string device = "CPU";
    ov::genai::LLMPipeline pipe(models_path, device);
    
    ov::genai::GenerationConfig config = pipe.get_generation_config();
    config.max_new_tokens = 512;
    config.do_sample = false;
    config.repetition_penalty = 1.1;

    std::function<bool(std::string)> streamer = [](std::string word) { 
        std::cout << word << std::flush;
        // Return flag corresponds whether generation should be stopped.
        // false means continue generation.
        return false; 
    };

    // Warmup inference for GPU reproducibility
    ov::genai::GenerationConfig warmupconfig = pipe.get_generation_config();
    warmupconfig.max_new_tokens = 5;
    warmupconfig.do_sample = false;
    pipe.generate("say something", warmupconfig);
    
    pipe.start_chat(start_message);
    std::cout << "question:\n";
    while (std::getline(std::cin, prompt)) {
        pipe.generate(prompt, config, streamer);
        std::cout << "\n----------\n"
            "question:\n";
    }
    pipe.finish_chat();
} catch (const std::exception& error) {
    try {
        std::cerr << error.what() << '\n';
    } catch (const std::ios_base::failure&) {}
    return EXIT_FAILURE;
} catch (...) {
    try {
        std::cerr << "Non-exception object thrown\n";
    } catch (const std::ios_base::failure&) {}
    return EXIT_FAILURE;
}
