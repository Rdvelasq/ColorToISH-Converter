#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int WIDTH = 1920;
int HEIGHT = 1440;
int imageSize = WIDTH * HEIGHT;

char coloredBallsImg [1440][1920];
char coloredSmokeImg [1440][1920];

unsigned char R[1440][1920], G[1440][1920], B[1440][1920];
float totalR = 0;
float totalG = 0;
float totalB = 0;

unsigned int intensityArr[1440][1920];

int main(){

  FILE *photoFile;
  
  photoFile = fopen("colored-balls33.data", "rb");
  if (photoFile == NULL)
  {
    cout << "unable to open image";
    return 1;
  }
  else{
    cout << "Open Colored Balls Image" << endl;
  }
  fread(R, 1, imageSize, photoFile);
  fread(G, 1, imageSize, photoFile);
  fread(B, 1, imageSize, photoFile);
  for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            int totalRGB = int(R[i][j]) + int(G[i][j]) + int(B[i][j]);
            int intensity = totalRGB / 3;
            intensityArr[i][j] = intensity;
            
            // We need to get values from 0-1 so we divde by 255 
            float normalizeR = float(R[i][j])/255.0;
            float normalizeG = float(G[i][j])/255.0;
            float normalizeB = float(B[i][j])/255.0;

            //vector<int> normalizedRGB = {normalizeR, normalizeG, normalizeB};
            vector<float> normalizedRGB;
            normalizedRGB.push_back(normalizeR);
            normalizedRGB.push_back(normalizeG);
            normalizedRGB.push_back(normalizeB);
            sort(normalizedRGB.begin(), normalizedRGB.end());
            // calculate min and max 
            float maxValue = normalizedRGB[normalizedRGB.size() - 1];
            float minValue = normalizedRGB[0];

            float luminosity = (maxValue + minValue) / 2;

            if(i <= 0 && j <= 100){
              cout << "Pixel (" << i << "," << j << "): (" 
              << float((R[i][j])) << ", "
              << float((G[i][j])) << ", "
              << float((B[i][j])) << ")" << endl;

              cout << "total RGB: " << totalRGB << "Intensity: " << intensity << endl;
              cout << " Normalized R: " << normalizeR << " Normalized G: " << normalizeG << " Normalized B: " << normalizeB << endl;
              cout << "Max: " << maxValue << " Min: " << minValue << endl;
              cout << "Lumin: " << luminosity << endl << endl;
            }
            
            
        }
    } 
  

  fclose(photoFile);
  
  return 0; 
}