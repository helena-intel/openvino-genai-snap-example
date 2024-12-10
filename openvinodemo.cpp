#include "openvino/genai/llm_pipeline.hpp"
#include <iostream>

// Very basic demo application for testing
// Usage: openvinodemo /path/to/model

int main(int argc, char* argv[]) {
   std::filesystem::path model_path = argv[1];
   std::string prompt = "why is the sky blue?";
   ov::genai::LLMPipeline pipe(model_path, argv[2]);
   ov::genai::GenerationConfig config = pipe.get_generation_config();
   config.max_new_tokens = 32;
   std::string result = pipe.generate(prompt, config);
   std::cout << prompt << result << std::endl;
}
