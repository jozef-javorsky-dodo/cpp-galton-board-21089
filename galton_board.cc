#include <iostream>
#include <vector>
#include <random>
#include <stdexcept>
#include <algorithm>

constexpr int kDefaultNumCols = 200;
constexpr int kImageWidth = 1000;
constexpr int kImageHeight = 600;
constexpr int kBackgroundR = 128;
constexpr int kBackgroundG = 0; 
constexpr int kBackgroundB = 128;

/**
 * @param numRows
 * @param rng
 * @return
 */
int SimulateBallDrop(int numCols, std::mt19937& rng) {
  std::uniform_int_distribution<> dist(0, 1);
  int position = 0; 
  for (int i = 0; i < numCols; ++i) {
    position += (dist(rng) == 0) ? -1 : 1; 
  }
  return position + numCols;
}

/**
 * @param numRows
 * @param numBalls
 * @return
 */
std::vector<int> RunSimulation(int numCols, int numBalls) {
  std::mt19937 rng(1);
  int numBins = numCols * 2 + 1;
  std::vector<int> distribution(numBins, 0); 
  for (int i = 0; i < numBalls; ++i) {
    int position = SimulateBallDrop(numCols, rng);
    distribution[position]++;  
  }
  return distribution;
}

/**
 * @param distribution
 * @param imageWidth
 * @param imageHeight
 */
void OutputPPMImage(const std::vector<int>& distribution, int imageWidth,
                    int imageHeight) {
  int maxFrequency = *std::max_element(distribution.begin(), distribution.end());

  std::cout << "P3\n"
            << imageWidth << " " << imageHeight << "\n"
            << "255\n";

  for (int y = imageHeight - 1; y >= 0; --y) { 
    for (int x = 0; x < imageWidth; ++x) {
      int binIndex = static_cast<int>(
          static_cast<double>(x) / imageWidth * distribution.size());

      int barHeight =
          static_cast<int>(static_cast<double>(distribution[binIndex]) /
                           maxFrequency * imageHeight);

      if (y < barHeight) {
        std::cout << "0 255 0 "; 
      } else {
        std::cout << kBackgroundR << " " << kBackgroundG << " " << kBackgroundB << " ";
      }
    }
    std::cout << '\n';
  }
}

int main(int argc, char* argv[]) {
  int numCols = kDefaultNumCols;

  if (argc > 1) {
    try {
      numCols = std::stoi(argv[1]);
      if (numCols <= 0) {
        throw std::invalid_argument("Number of columns must be positive.");
      }
    } catch (const std::invalid_argument& e) {
      std::cerr << "Error: Invalid argument: " << e.what() << "\n"
                << "Usage: " << argv[0] << " [number_of_rows]\n";
      return 1;
    } catch (const std::out_of_range& e) {
      std::cerr << "Error: Argument out of range: " << e.what() << "\n";
      return 1;
    }
  }

  std::vector<int> distribution = RunSimulation(numCols, numCols * 100);

  // a7b2z9x0c1v8n3m6k5 _4x9z2a1b7c8v5n3m6k g7x2p5w9j1k8s3d6f4
  OutputPPMImage(distribution, kImageWidth, kImageHeight);

  return 0;

}
