#include "openvino/genai/llm_pipeline.hpp"
#include <iostream>

// Very basic demo application for testing
// Usage: ./openvinodemo model_path prompt device

int main(int argc, char* argv[]) {
   std::filesystem::path model_path = argv[1];
   std::string prompt = argv[2];
   ov::genai::LLMPipeline pipe(model_path, argv[3]);
   ov::genai::GenerationConfig config = pipe.get_generation_config();
   config.max_new_tokens = 32;
   std::string result = pipe.generate(prompt, config);
   std::cout << prompt << result << std::endl;
}
