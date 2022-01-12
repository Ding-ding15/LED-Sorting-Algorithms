#include <FastLED.h>
#include <OneButton.h>
#include <stdio.h>

#define NUM_LEDS 300
#define LED_PIN 2
#define BTN_PIN 3

CRGB leds[NUM_LEDS];

uint8_t patternCounter = 0;
uint8_t hue = 0;
uint8_t paletteIndex = 0;

//button between pin 3 and gnd
OneButton btn = OneButton(BTN_PIN, true, true);


void setup() {
  // put your setup code here, to run once:
  FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(50);

  btn.attachClick(nextPattern);

  int arr[NUM_LEDS];
}


void loop() {
  
  switch (patternCounter) {
    case 0:
      bubbleSort();
    case 1:
      insertionSort();
      break;
    case 2:
      insertionSort();
      break;
    case 3:
      bubbleSort();
      break;
  }


  FastLED.show();
  btn.tick();
}


void nextPattern() {
  patternCounter = (patternCounter + 1) % 4;  //change # after modulo to # of patterns
}

void bubbleSort() {
  fill_solid(leds, NUM_LEDS, CHSV(0, 0, 0));
  FastLED.show();
  int led[NUM_LEDS];                          //create array for sorting
  for (int i = 0; i < NUM_LEDS; i++) {        //fill array with random 8-bit numbers
    int j = random8();
    led[i] = j;
    lightDriver(j, i);
  }

    for (int i = 0; i < NUM_LEDS - 1; i++) {
      for (int j = 0; j < NUM_LEDS - 1 - i; j++) {
        if (led[j] > led[j + 1]) {
          lightDriver(led[j + 1], j);
          lightDriver(led[j], j + 1);
          int temp = led[j + 1];
          led[j + 1] = led[j];
          led[j] = temp;
        }
      }
    }
  delay(10000);
  }



void insertionSort() {
  fill_solid(leds, NUM_LEDS, CHSV(0, 0, 0));
  FastLED.show();
}

void merge(int arr[], int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;
  
    /* create temp arrays */
    int L[n1], R[n2];
  
    /* Copy data to temp arrays L[] and R[] */
    for (i = 0; i < n1; i++) {
        L[i] = arr[l + i];
    }
    for (j = 0; j < n2; j++) {
        R[j] = arr[m + 1 + j];
    }
  
    /* Merge the temp arrays back into arr[l..r]*/
    i = 0; // Initial index of first subarray
    j = 0; // Initial index of second subarray
    k = l; // Initial index of merged subarray
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
  
    /* Copy the remaining elements of L[], if there
    are any */
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
  
    /* Copy the remaining elements of R[], if there
    are any */
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}
  
/* l is for left index and r is right index of the
sub-array of arr to be sorted */
void mergeSort(int arr[], int l, int r)       //dont know how to get it to work with lights
{
  for (int i = 0; i < NUM_LEDS; i++) {        //fill array with random 8-bit numbers
    int j = random8();
    arr[i] = j;
    lightDriver(j, i);
  }
    if (l < r) {
        // Same as (l+r)/2, but avoids overflow for
        // large l and h
        int m = l + (r - l) / 2;
  
        // Sort first and second halves
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
  
        merge(arr, l, m, r);
    }
}
  


void quickSort(int num[], int l, int r)
{
  if (l >= r) 
    return;
  int m = l, n = r, x = num[l];
  while (m < n)
  {
    while (m < n && num[n] >= x) 
      n--;
    if (m < n)
    {
      lightDriver(num[n], m);
      num[m++] = num[n]; 
    }

    while (m < n && num[m] <= x) 
      m++;
    if (m < n)
    {
      lightDriver(num[m], n);
      num[n--] = num[m];
    }
  }
  num[m] = x;               //put the inital x into m element
  lightDriver(x, m);
  quickSort(num, l, m - 1); //use m as mid value, use recursive call
  quickSort(num, m + 1, r);
}

void lightDriver(int val, int index) {
  leds[index] = CHSV(val, 255, 100);
  FastLED.show();
  delay(1);
}