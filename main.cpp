#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>

using namespace std;

int WIDTH = 1920;
int HEIGHT = 1280;
int imageSize = WIDTH * HEIGHT;

//char coloredBallsImg [1280][1920];
//char coloredSmokeImg [1280][1920];

unsigned char R[1280][1920], G[1280][1920], B[1280][1920];

char intensityArr[1280][1920];
char saturationArr[1280][1920];
char hueArr[1280][1920];


void calculateIntensity(int i, int j){
  // Current R G B Values
  int redVal = int(R[i][j]);
  int greenVal = int(G[i][j]);
  int blueVal = int(B[i][j]);
            
  // Intensity R + G + B / 3
  int lightness = redVal + greenVal + blueVal;

  vector<int> rgbArr;
  rgbArr.push_back(redVal);
  rgbArr.push_back(greenVal);
  rgbArr.push_back(blueVal);
            
  // calculate min 
  sort(rgbArr.begin(), rgbArr.end());
  int minValue = rgbArr[0];

  float intensity = lightness / 3;
  //covert back to a scale of 0,255
  intensityArr[i][j] = round(intensity);
}

int getMinValue(int i, int j){
  int redVal = int(R[i][j]);
  int greenVal = int(G[i][j]);
  int blueVal = int(B[i][j]);

  vector<int> rgbArr;
  rgbArr.push_back(redVal);
  rgbArr.push_back(greenVal);
  rgbArr.push_back(blueVal);
            
  // calculate min 
  sort(rgbArr.begin(), rgbArr.end());
  int minValue = rgbArr[0];
  return minValue;
}

void calculateSaturation(int i, int j, int minValue){
  int redVal = int(R[i][j]);
  int greenVal = int(G[i][j]);
  int blueVal = int(B[i][j]);
  int lightness = redVal + greenVal + blueVal;
  float saturation;
  // R G B are the same then the color is black

  if(redVal == greenVal && greenVal == blueVal){  
    //Therefor there is 0 saturation
    saturation = 0;
  }
  else{
    float numerator = 3*minValue;
    saturation = 1 - (numerator / lightness);
  }
  
  //covert back to a scale of 0,255
  saturationArr[i][j] = round(saturation*255);

}

void calculateHue(int i, int j){
  int redVal = int(R[i][j]);
  int greenVal = int(G[i][j]);
  int blueVal = int(B[i][j]);

  //HUE
  // (R-G) + (R-B) / 2 sqrt((R-G)^2 + (R-B)(G-B))
  // float hue = ((int(R[i][j]) - int(G[i][j])) + (int(R[i][j]) + int(B[i][j]))) / 2 * sqrt((pow((int(R[i][j]) - int(G[i][j])),2))) + (int(R[i][j]) - int(B[i][j])) * (int(G[i][j]) - int(B[i][j]));
  int numerator = ((redVal - greenVal) + (redVal - blueVal));
  float denominator = 2*sqrt(pow(redVal-greenVal,2) + (redVal - blueVal) * (greenVal - blueVal));
  //gives a value from 0,1
  float hue = numerator/denominator;
  float hueAngle;
  if(greenVal >= blueVal){
    //convert to degrees
    hueAngle = acos(hue) * 180/M_PI;
  }
  else{
    hueAngle = 360 - acos(hue) * 180/M_PI;
  }
  //covert angle between values 1,255
  float scaledHue = 1 + (hueAngle/360) * 254;
  hueArr[i][j] = round(scaledHue);
}

int main(){
  
  FILE *photoFile;
  
  photoFile = fopen("image1.raw", "rb");
  if (photoFile == NULL)
  {
    cout << "unable to open image";
    return 1;
  }
  else{
    cout << "Opend 1st Image" << endl;
  }
  fread(R, 1, imageSize, photoFile);
  fread(G, 1, imageSize, photoFile);
  fread(B, 1, imageSize, photoFile);
  fclose(photoFile);

  for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
          
          int minValue = getMinValue(i,j);
          calculateIntensity(i, j);
          calculateSaturation(i,j, minValue);
          calculateHue(i, j);
            
        }
    } 
    FILE *outputFile;

    outputFile = fopen("hueFile1.raw", "wb");
    fwrite(hueArr,1,imageSize, outputFile);
    fclose(outputFile);

    outputFile = fopen("saturationFile1.raw", "wb");
    fwrite(saturationArr,1,imageSize, outputFile);
    fclose(outputFile);

    outputFile = fopen("intensityFile1.raw", "wb");
    fwrite(intensityArr,1,imageSize, outputFile);
    fclose(outputFile);

  photoFile = fopen("image2.raw", "rb");
  if (photoFile == NULL)
  {
    cout << "unable to open image";
    return 1;
  }
  else{
    cout << "Opend 2nd Image" << endl;
  }
  fread(R, 1, imageSize, photoFile);
  fread(G, 1, imageSize, photoFile);
  fread(B, 1, imageSize, photoFile);
  fclose(photoFile);  
  for (int i = 0; i < HEIGHT; i++){
    for (int j = 0; j < WIDTH; j++)
    {
      int minValue = getMinValue(i,j);
      calculateIntensity(i, j);
      calculateSaturation(i,j, minValue);
      calculateHue(i, j);
    }
    
  }

  outputFile = fopen("hueFile2.raw", "wb");
  fwrite(hueArr,1,imageSize, outputFile);
  fclose(outputFile);

  outputFile = fopen("saturationFile2.raw", "wb");
  fwrite(saturationArr,1,imageSize, outputFile);
  fclose(outputFile);

  outputFile = fopen("intensityFile2.raw", "wb");
  fwrite(intensityArr,1,imageSize, outputFile);
  fclose(outputFile);
  
  return 0; 
}