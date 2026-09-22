#include <TFT_eSPI.h>

#define LEFT_BUTTON 25
#define CENTER_BUTTON 32
#define RIGHT_BUTTON 33

TFT_eSPI tft = TFT_eSPI();
TFT_eSprite spr = TFT_eSprite(&tft);

// Main Structs
struct Edge {
  int a;
  int b;
};
struct Point3D {
  float x;
  float y;
  float z;
};
struct DiceShape {
  const Point3D* vertices;
  const Edge* edges;
  int vertexCount;
  int edgeCount;
  int sides;
  float scale;
};

// Constants for some shapes
const float phi = (1.0 + sqrt(5.0)) / 2.0;
const float invPhi = 1.0 / phi;
const float C0 = (sqrt(5.0) - 1.0) / 4.0;
const float C1 = (sqrt(5.0) + 1.0) / 4.0;
const float C2 = (sqrt(5.0) + 3.0) / 4.0;

// Shape Definitions & Drawing Orders
const Point3D tetrahedron[4] = {
  { 1, 1, 1 },
  { 1, -1, -1 },
  { -1, 1, -1 },
  { -1, -1, 1 }
};

const Edge tetrahedronOrder[] = {
  {0, 1},
  {0, 2},
  {0, 3},
  {1, 2},
  {1, 3},
  {2, 3}
};

const Point3D cube[8] = {
  { 1, 1, 1 },
  { 1, -1, 1 },
  { -1, -1, 1 },
  { -1, 1, 1 },
  { -1, 1, -1 },
  { 1, 1, -1 },
  { 1, -1, -1 },
  { -1, -1, -1 },
};
const Edge cubeOrder[] = {
  { 0, 1 },
  { 1, 2 },
  { 2, 3 },
  { 3, 0 },

  { 4, 5 },
  { 5, 6 },
  { 6, 7 },
  { 7, 4 },

  { 0, 5 },
  { 1, 6 },
  { 2, 7 },
  { 3, 4 }
};

const Point3D octahedron[6] = {
  {1,0,0},
  {0,1,0},
  {0,0,1},
  {-1,0,0},
  {0,-1,0},
  {0,0,-1}
};
const Edge octahedronOrder[] = {
  {0, 1},
  {0, 2},
  {0, 4},
  {0, 5},

  {3, 1},
  {3, 2},
  {3, 4},
  {3, 5},

  {1, 2},
  {1, 5},
  {4, 2},
  {4, 5}
};

const Point3D pentagonalTrapezohedron[12] = {
  { 0.0,  C0,   C1 },   // 0
  { 0.0,  C0,  -C1 },   // 1
  { 0.0, -C0,   C1 },   // 2
  { 0.0, -C0,  -C1 },   // 3

  { 0.5,  0.5,  0.5 },  // 4
  { 0.5,  0.5, -0.5 },  // 5
  {-0.5, -0.5,  0.5 },  // 6
  {-0.5, -0.5, -0.5 },  // 7

  { C2,  -C1,  0.0 },   // 8
  {-C2,   C1,  0.0 },   // 9

  { C0,   C1,  0.0 },   // 10
  {-C0,  -C1,  0.0 }    // 11
};
const Edge pentagonalTrapezohedronOrder[] = {
  {0, 2},
  {0, 4},
  {0, 9},

  {1, 3},
  {1, 5},
  {1, 9},

  {2, 6},
  {2, 8},

  {3, 7},
  {3, 8},

  {4, 8},
  {4, 10},

  {5, 8},
  {5, 10},

  {6, 9},
  {6, 11},

  {7, 9},
  {7, 11},

  {8, 11},
  {9, 10}
};

const Point3D dodecahedron[20] = {
  { 1,  1,  1},   // 0
  { 1,  1, -1},   // 1
  { 1, -1,  1},   // 2
  { 1, -1, -1},   // 3
  {-1,  1,  1},   // 4
  {-1,  1, -1},   // 5
  {-1, -1,  1},   // 6
  {-1, -1, -1},   // 7

  {0,  invPhi,  phi},   // 8
  {0,  invPhi, -phi},   // 9
  {0, -invPhi,  phi},   // 10
  {0, -invPhi, -phi},   // 11

  { invPhi,  phi, 0},   // 12
  { invPhi, -phi, 0},   // 13
  {-invPhi,  phi, 0},   // 14
  {-invPhi, -phi, 0},   // 15

  { phi, 0,  invPhi},   // 16
  { phi, 0, -invPhi},   // 17
  {-phi, 0,  invPhi},   // 18
  {-phi, 0, -invPhi}    // 19
};

Edge dodecahedronOrder[] = {
  {0, 8},
  {0, 12},
  {0, 16},

  {1, 9},
  {1, 12},
  {1, 17},

  {2, 10},
  {2, 13},
  {2, 16},

  {3, 11},
  {3, 13},
  {3, 17},

  {4, 8},
  {4, 14},
  {4, 18},

  {5, 9},
  {5, 14},
  {5, 19},

  {6, 10},
  {6, 15},
  {6, 18},

  {7, 11},
  {7, 15},
  {7, 19},

  {8, 10},
  {9, 11},

  {12, 14},
  {13, 15},

  {16, 17},
  {18, 19}
};

Point3D icosahedron[12] = {
  {0,  1,  phi},   // 0
  {0,  1, -phi},   // 1
  {0, -1,  phi},   // 2
  {0, -1, -phi},   // 3

  { 1,  phi, 0},   // 4
  { 1, -phi, 0},   // 5
  {-1,  phi, 0},   // 6
  {-1, -phi, 0},   // 7

  { phi, 0,  1},   // 8
  { phi, 0, -1},   // 9
  {-phi, 0,  1},   // 10
  {-phi, 0, -1}    // 11
};

Edge icosahedronOrder[] = {
  {0, 2},
  {0, 4},
  {0, 6},
  {0, 8},
  {0, 10},

  {1, 3},
  {1, 4},
  {1, 6},
  {1, 9},
  {1, 11},

  {2, 5},
  {2, 7},
  {2, 8},
  {2, 10},

  {3, 5},
  {3, 7},
  {3, 9},
  {3, 11},

  {4, 6},
  {4, 8},
  {4, 9},

  {5, 7},
  {5, 8},
  {5, 9},

  {6, 10},
  {6, 11},

  {7, 10},
  {7, 11},

  {8, 9},
  {10, 11}
};

// Dice Shapes
DiceShape d4 = {
  tetrahedron,
  tetrahedronOrder,
  sizeof(tetrahedron) / sizeof(tetrahedron[0]),
  sizeof(tetrahedronOrder) / sizeof(tetrahedronOrder[0]),
  4,
  60
};

DiceShape d6 = {
  cube,
  cubeOrder,
  sizeof(cube) / sizeof(cube[0]),
  sizeof(cubeOrder) / sizeof(cubeOrder[0]),
  6,
  60
};

DiceShape d8 = {
  octahedron,
  octahedronOrder,
  sizeof(octahedron) / sizeof(octahedron[0]),
  sizeof(octahedronOrder) / sizeof(octahedronOrder[0]),
  8,
  90
};

DiceShape d10 = {
  pentagonalTrapezohedron,
  pentagonalTrapezohedronOrder,
  sizeof(pentagonalTrapezohedron) / sizeof(pentagonalTrapezohedron[0]),
  sizeof(pentagonalTrapezohedronOrder) / sizeof(pentagonalTrapezohedronOrder[0]),
  10,
  80
};

DiceShape d12 = {
  dodecahedron,
  dodecahedronOrder,
  sizeof(dodecahedron) / sizeof(dodecahedron[0]),
  sizeof(dodecahedronOrder) / sizeof(dodecahedronOrder[0]),
  12,
  50
};

DiceShape d20 = {
  icosahedron,
  icosahedronOrder,
  sizeof(icosahedron) / sizeof(icosahedron[0]),
  sizeof(icosahedronOrder) / sizeof(icosahedronOrder[0]),
  20,
  50
};

DiceShape dices[] = {
  d4,
  d6,
  d8,
  d10,
  d12,
  d20
};

// Rotation info stored instead of a second shape for efficiency
float rotInfo[] = { 0, 0, 0 }; 

// Menu stuff
String menuList[] = {
  "d4 at",
  "d6 at",
  "d8 at",
  "d10 at",
  "d12 at",
  "d20 at"
};

int menuCount = sizeof(menuList) / sizeof(menuList[0]);
int selectedIndex = 0;

bool isRollingDice = false;
float y_offset = 60;
int left_margin = 14;
float diceSpeed = 4;
float theta = radians(5.0);
int diceResult;

unsigned long lastFrameTime = 0;
unsigned long lastButtonTime = 0;

int lastLeftButtonState = HIGH;
int lastRightButtonState = HIGH;
int lastCenterButtonState = HIGH;
int textMargin = 30;

void setup() {
  tft.begin();
  tft.setRotation(0);
  tft.fillScreen(TFT_BLACK);

  pinMode(LEFT_BUTTON, INPUT_PULLUP);
  pinMode(CENTER_BUTTON, INPUT_PULLUP);
  pinMode(RIGHT_BUTTON, INPUT_PULLUP);

  spr.setColorDepth(8);   // Works with 8 bit due to RAM issues

  spr.createSprite(240, 240); // Sprite used for smoother animations

  Serial.begin(115200);
}

// Apply transformation to a point
Point3D rotate(Point3D coord) {
  Point3D output = coord;

  // X
  float old_y = output.y;
  float old_z = output.z;

  output.y = old_y * cos(rotInfo[0]) - old_z * sin(rotInfo[0]);
  output.z = old_y * sin(rotInfo[0]) + old_z * cos(rotInfo[0]);

  // Y
  float old_x = output.x;
  old_z = output.z;

  output.x = old_x * cos(rotInfo[1]) + old_z * sin(rotInfo[1]);
  output.z = -old_x * sin(rotInfo[1]) + old_z * cos(rotInfo[1]);

  // Z
  old_x = output.x;
  old_y = output.y;

  output.x = old_x * cos(rotInfo[2]) - old_y * sin(rotInfo[2]);
  output.y = old_x * sin(rotInfo[2]) + old_y * cos(rotInfo[2]);

  return output;
}

// Scale the values for screen
float norm(float val, float scale) {
  return val * scale + 120;
}

void diceView(DiceShape shape) {
  spr.fillSprite(TFT_BLACK);

  rotInfo[0] += theta;
  rotInfo[1] += theta * 0.7;
  rotInfo[2] += theta * 0.4;

  for (int i = 0; i < shape.edgeCount; i++) {
    int a = shape.edges[i].a;
    int b = shape.edges[i].b;
    Point3D a_new = rotate(shape.vertices[a]);
    Point3D b_new = rotate(shape.vertices[b]);
    spr.drawLine(norm(a_new.x, shape.scale), norm(a_new.y, shape.scale) + y_offset, norm(b_new.x, shape.scale), norm(b_new.y, shape.scale) + y_offset, TFT_LIGHTGREY);
  }

  String current = menuList[selectedIndex];

  int spaceIndex = current.indexOf(' ');
  String diceName = current.substring(0, spaceIndex);

  if (y_offset > 0) {
    spr.setTextColor(TFT_WHITE);
    spr.setTextDatum(MC_DATUM);
    spr.setTextSize(5);
    spr.drawString(String(random(1, shape.sides + 1)), 120, 120 + y_offset);
    y_offset = y_offset - diceSpeed;
  } else {
    if (diceResult == 1) {
      spr.setTextSize(8);
      spr.setTextColor(TFT_RED);
    } else if (diceResult == shape.sides) {
      spr.setTextSize(8);
      spr.setTextColor(TFT_GREEN);
    } else {
      spr.setTextSize(8);
      spr.setTextColor(TFT_WHITE);
    }
    spr.drawString(String(diceResult), 120, 120);
  }
  spr.pushSprite(0,0);
}

void loop() {
  int buttonState = digitalRead(LEFT_BUTTON);
  int leftButtonState = digitalRead(LEFT_BUTTON);
  int centerButtonState = digitalRead(CENTER_BUTTON);
  int rightButtonState = digitalRead(RIGHT_BUTTON);

  if (lastCenterButtonState == HIGH && centerButtonState == LOW) {
    isRollingDice = true;
    diceResult = random(1, dices[selectedIndex].sides + 1);
  }

  if (isRollingDice) { // Show Dice Rolling View
    if (millis() - lastFrameTime >= 70) {
      lastFrameTime = millis();
      
      diceView(dices[selectedIndex]);
    }
    if (lastRightButtonState == HIGH && rightButtonState == LOW) {
      isRollingDice = false;
      y_offset = 60;
    }
  } else { // Show Menu
    if (millis() - lastFrameTime >= 100) {
      lastFrameTime = millis();

      spr.fillSprite(TFT_BLACK);
      spr.setTextDatum(ML_DATUM);

      spr.setTextColor(TFT_WHITE);
      spr.setTextSize(4);
      spr.drawString("ZarMatik", left_margin, 35);

      for (int i = 0; i < menuCount; i++) {
        if (i == selectedIndex) {
          spr.setTextColor(TFT_GREEN);
        } else {
          spr.setTextColor(TFT_WHITE);
        }
        spr.setTextSize(3);
        spr.drawString(menuList[i], left_margin, 68 + (i * textMargin));
      }
      spr.pushSprite(0,0);
    }

    if (lastLeftButtonState == HIGH && leftButtonState == LOW) {
      if (millis() - lastButtonTime >= 100) {
        lastButtonTime = millis();
        if (selectedIndex == 0) {
          selectedIndex = menuCount - 1;
        } else {
          selectedIndex--;
        }
      }
    }


    if (lastRightButtonState == HIGH && rightButtonState == LOW) {
      if (millis() - lastButtonTime >= 100) {
        lastButtonTime = millis();
        if (selectedIndex == menuCount - 1) {
          selectedIndex = 0;
        } else {
          selectedIndex++;
        }
      }
    }
  }

  lastLeftButtonState = leftButtonState;
  lastRightButtonState = rightButtonState;
  lastCenterButtonState = centerButtonState;
}
