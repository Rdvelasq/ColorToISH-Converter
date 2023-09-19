#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>

using namespace std;

int WIDTH = 1920;
int HEIGHT = 1440;
int imageSize = WIDTH * HEIGHT;

char coloredBallsImg [1440][1920];
char coloredSmokeImg [1440][1920];

unsigned char R[1440][1920], G[1440][1920], B[1440][1920];

float intensityArr[1440][1920];
float saturationArr[1440][1920];
float hueArr[1440][1920];

int main(){

  FILE *photoFile;
  
  photoFile = fopen("colored-balls.raw", "rb");
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
            int redVal = int(R[i][j]);
            int greenVal = int(G[i][j]);
            int blueVal = int(B[i][j]);

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
            
            // calculate min and max 
            sort(normalizedRGB.begin(), normalizedRGB.end());
            float maxValue = normalizedRGB[normalizedRGB.size() - 1];
            float minValue = normalizedRGB[0];

            float luminosity = (maxValue + minValue) / 2;
            //covert back to a scale of 0,255
            intensityArr[i][j] = round(luminosity*255);
            
            float saturation;
            // R G B are the same then the color is black
            if(int(R[i][j] == int(G[i][j] && int(G[i][j] == int(B[i][j]))))){  
              //Therefor there is 0 saturation
              saturation = 0;
            }
            else{
              float numerator = 3*minValue;
              saturation = 1 - (numerator / luminosity);
            }
            
            //covert back to a scale of 0,255
            saturationArr[i][j] = round(saturation*255);

            //HUE
            // (R-G) + (R-B) / 2 sqrt((R-G)^2 + (R-B)(G-B))
            // float hue = ((int(R[i][j]) - int(G[i][j])) + (int(R[i][j]) + int(B[i][j]))) / 2 * sqrt((pow((int(R[i][j]) - int(G[i][j])),2))) + (int(R[i][j]) - int(B[i][j])) * (int(G[i][j]) - int(B[i][j]));
            float numerator = ((redVal - greenVal) + (redVal - blueVal));
            float denominator = 2*sqrt(pow(redVal-greenVal,2) + (redVal - blueVal) * (greenVal - blueVal));
            float hue = numerator/denominator;
            float hueAngle;
            if(greenVal >= blueVal){
              hueAngle = acos(hue) * 180/M_PI;
            }
            else{
              hueAngle = 360 - acos(hue) * 180/M_PI;
            }


            if(i <= 0 && j <= 10){
              cout << "Pixel (" << i << "," << j << "): (" 
              << float((R[i][j])) << ", "
              << float((G[i][j])) << ", "
              << float((B[i][j])) << ")" << endl;

              cout << "total RGB: " << totalRGB << " Intensity: " << intensity << endl;
              cout << " Normalized R: " << normalizeR << " Normalized G: " << normalizeG << " Normalized B: " << normalizeB << endl;
              cout << "Max: " << maxValue << " Min: " << minValue << endl;
              cout << "Lumin: " << round(luminosity*255) << endl;
              cout << "Saturation: " << round(saturation*255) << endl;
              cout << "HUE: " << hue << endl;
              cout << "Angle: " << hueAngle << endl << endl;
            }
            
            
        }
    } 
  

  fclose(photoFile);
  
  return 0; 
}