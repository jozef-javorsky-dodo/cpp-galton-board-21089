#include <algorithm>
#include <chrono>
#include <iostream>
#include <random>
#include <stdexcept>
#include <vector>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

constexpr int kDefaultNumCols = 200;
constexpr int kBoardWidth = 800;
constexpr int kBoardHeight = 400;
constexpr int kNumBalls = 20000;

int SimulateBallDrop(int numCols, std::mt19937 &rng) {
  std::uniform_int_distribution<> dist(0, 1);
  int position = 0;
  for (int i = 0; i < numCols; ++i) {
    position += (dist(rng) == 0) ? -1 : 1;
  }
  return position + numCols;
}

std::vector<int> RunSimulation(int numCols, int numBalls) {
  unsigned seed = std::chrono::high_resolution_clock::now()
                      .time_since_epoch()
                      .count();
  std::mt19937 rng(seed);
  int numBins = numCols * 2 + 1;
  std::vector<int> distribution(numBins, 0);
  for (int i = 0; i < numBalls; ++i) {
    int final_position = SimulateBallDrop(numCols, rng);
    distribution[final_position]++;
  }
  return distribution;
}

void GenerateImage(const std::vector<int> &distribution, int numCols) {
  int max_count = *std::max_element(distribution.begin(), distribution.end());
  std::vector<unsigned char> pixels(kBoardWidth * kBoardHeight * 3);
  for (size_t i = 0; i < pixels.size(); i += 3) {
    pixels[i] = 50;
    pixels[i + 1] = 50;
    pixels[i + 2] = 50;
  }
  int numBins = distribution.size();
  float bar_width = static_cast<float>(kBoardWidth) / numBins;
  for (int bin_index = 0; bin_index < numBins; ++bin_index) {
    if (distribution[bin_index] == 0) {
      continue;
    }
    float bar_height_ratio =
        static_cast<float>(distribution[bin_index]) / max_count;
    int bar_height = static_cast<int>(bar_height_ratio * kBoardHeight);
    int x_start = static_cast<int>(bin_index * bar_width);
    int x_end = static_cast<int>((bin_index + 1) * bar_width);
    for (int x = x_start; x < x_end && x < kBoardWidth; ++x) {
      for (int y = 0; y < bar_height && y < kBoardHeight; ++y) {
        int pixel_index = ((kBoardHeight - 1 - y) * kBoardWidth + x) * 3;
        pixels[pixel_index] = 0;
        pixels[pixel_index + 1] = 255;
        pixels[pixel_index + 2] = 0;
      }
    }
  }
  stbi_write_png("galton_board.png", kBoardWidth, kBoardHeight, 3,
                 pixels.data(), kBoardWidth * 3);
}

int main(int argc, char *argv[]) {
  int numCols = kDefaultNumCols;
  if (argc > 1) {
    try {
      numCols = std::stoi(argv[1]);
      if (numCols <= 0) {
        throw std::invalid_argument("Number of columns must be positive.");
      }
    } catch (const std::invalid_argument &e) {
      std::cerr << "Error: Invalid argument: " << e.what() << "\n"
                << "Usage: " << argv[0] << " [number_of_columns]\n";
      return 1;
    } catch (const std::out_of_range &e) {
      std::cerr << "Error: Argument out of range: " << e.what() << "\n";
      return 1;
    }
  }
  std::vector<int> distribution = RunSimulation(numCols, kNumBalls);
  GenerateImage(distribution, numCols);
  std::cout
      << "Galton Board simulation completed. Image saved to: galton_board.png"
      << std::endl;
  return 0;
}
