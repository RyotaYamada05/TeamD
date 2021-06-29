xof 0302txt 0064
template Header {
 <3D82AB43-62DA-11cf-AB39-0020AF71E433>
 WORD major;
 WORD minor;
 DWORD flags;
}

template Vector {
 <3D82AB5E-62DA-11cf-AB39-0020AF71E433>
 FLOAT x;
 FLOAT y;
 FLOAT z;
}

template Coords2d {
 <F6F23F44-7686-11cf-8F52-0040333594A3>
 FLOAT u;
 FLOAT v;
}

template Matrix4x4 {
 <F6F23F45-7686-11cf-8F52-0040333594A3>
 array FLOAT matrix[16];
}

template ColorRGBA {
 <35FF44E0-6C7C-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
 FLOAT alpha;
}

template ColorRGB {
 <D3E16E81-7835-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
}

template IndexedColor {
 <1630B820-7842-11cf-8F52-0040333594A3>
 DWORD index;
 ColorRGBA indexColor;
}

template Boolean {
 <4885AE61-78E8-11cf-8F52-0040333594A3>
 WORD truefalse;
}

template Boolean2d {
 <4885AE63-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template MaterialWrap {
 <4885AE60-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template TextureFilename {
 <A42790E1-7810-11cf-8F52-0040333594A3>
 STRING filename;
}

template Material {
 <3D82AB4D-62DA-11cf-AB39-0020AF71E433>
 ColorRGBA faceColor;
 FLOAT power;
 ColorRGB specularColor;
 ColorRGB emissiveColor;
 [...]
}

template MeshFace {
 <3D82AB5F-62DA-11cf-AB39-0020AF71E433>
 DWORD nFaceVertexIndices;
 array DWORD faceVertexIndices[nFaceVertexIndices];
}

template MeshFaceWraps {
 <4885AE62-78E8-11cf-8F52-0040333594A3>
 DWORD nFaceWrapValues;
 Boolean2d faceWrapValues;
}

template MeshTextureCoords {
 <F6F23F40-7686-11cf-8F52-0040333594A3>
 DWORD nTextureCoords;
 array Coords2d textureCoords[nTextureCoords];
}

template MeshMaterialList {
 <F6F23F42-7686-11cf-8F52-0040333594A3>
 DWORD nMaterials;
 DWORD nFaceIndexes;
 array DWORD faceIndexes[nFaceIndexes];
 [Material]
}

template MeshNormals {
 <F6F23F43-7686-11cf-8F52-0040333594A3>
 DWORD nNormals;
 array Vector normals[nNormals];
 DWORD nFaceNormals;
 array MeshFace faceNormals[nFaceNormals];
}

template MeshVertexColors {
 <1630B821-7842-11cf-8F52-0040333594A3>
 DWORD nVertexColors;
 array IndexedColor vertexColors[nVertexColors];
}

template Mesh {
 <3D82AB44-62DA-11cf-AB39-0020AF71E433>
 DWORD nVertices;
 array Vector vertices[nVertices];
 DWORD nFaces;
 array MeshFace faces[nFaces];
 [...]
}

Header{
1;
0;
1;
}

Mesh {
 36;
 36.17291;15.66560;-13.76656;,
 36.16362;0.15939;-13.76656;,
 0.05518;-0.52256;-13.76656;,
 0.05518;14.39476;-13.76656;,
 38.99460;18.58680;-10.94646;,
 0.05518;17.21675;-10.94629;,
 0.05518;17.21675;11.61858;,
 38.99462;18.58680;11.61876;,
 36.16362;0.15939;14.43885;,
 36.17291;15.66560;14.43885;,
 0.05518;14.39476;14.43886;,
 0.05518;-0.52256;14.43886;,
 0.05518;-0.52256;14.43886;,
 0.05518;14.39476;14.43886;,
 0.05518;17.21675;11.61858;,
 0.05518;17.21675;-10.94629;,
 38.99462;18.58680;11.61876;,
 38.87106;0.05402;11.89398;,
 38.87106;0.05402;-11.22170;,
 38.99460;18.58680;-10.94646;,
 23.99865;-17.00641;-13.76656;,
 -0.08083;-20.90217;-13.76656;,
 25.30048;-19.09489;12.16915;,
 25.30048;-19.09489;-11.49687;,
 -0.08083;-20.90217;14.43886;,
 23.99866;-17.00641;14.43886;,
 38.87106;0.05402;11.89398;,
 25.30048;-19.09489;12.16915;,
 -0.09617;-23.20376;12.16929;,
 -0.09617;-23.20376;-11.49699;,
 25.30048;-19.09489;-11.49687;,
 -0.08083;-20.90217;14.43886;,
 -0.09617;-23.20376;12.16929;,
 -0.09617;-23.20376;-11.49699;,
 23.99866;-17.00641;14.43886;,
 36.16362;0.15939;14.43885;;
 
 24;
 4;0,1,2,3;,
 4;4,5,6,7;,
 4;8,9,10,11;,
 3;12,13,2;,
 3;13,14,2;,
 3;14,15,2;,
 3;15,3,2;,
 4;16,17,18,19;,
 4;1,20,21,2;,
 4;17,22,23,18;,
 4;4,0,3,5;,
 4;24,25,8,11;,
 4;9,7,6,10;,
 4;18,1,0,19;,
 4;8,26,7,9;,
 4;27,28,29,30;,
 4;23,20,1,18;,
 3;31,12,32;,
 3;12,2,32;,
 3;32,2,33;,
 3;2,21,33;,
 4;34,22,17,35;,
 4;33,21,20,23;,
 4;24,28,27,25;;
 
 MeshMaterialList {
  30;
  24;
  26,
  26,
  26,
  26,
  26,
  26,
  26,
  26,
  26,
  26,
  26,
  26,
  26,
  26,
  26,
  26,
  0,
  0,
  18,
  18,
  0,
  26,
  26,
  26;;
  Material {
   0.400000;0.400000;0.400000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.000000;0.000000;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.080000;0.080000;0.080000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.752000;0.160000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.080000;0.080000;0.080000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.048000;0.048000;0.048000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.632000;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.000000;0.336000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.000000;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.048000;0.048000;0.048000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.048000;0.048000;0.048000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.048000;0.048000;0.048000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.048000;0.048000;0.048000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.048000;0.048000;0.048000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.632000;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.632000;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.632000;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.632000;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.000000;0.336000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.000000;0.336000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.000000;0.336000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.000000;0.336000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.000000;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.000000;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.000000;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.048000;0.048000;0.048000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.780800;0.796800;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.000000;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.008000;0.008000;0.008000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.000000;0.368000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  29;
  0.000000;0.000000;-1.000000;,
  0.000000;0.000000;1.000000;,
  -0.032487;0.923308;-0.382685;,
  -0.013457;0.382445;-0.923880;,
  -0.032487;0.923308;0.382685;,
  -0.013457;0.382445;0.923880;,
  0.874054;-0.281134;-0.396224;,
  0.351531;-0.112846;-0.929350;,
  0.256011;0.271238;-0.927841;,
  0.351532;-0.112847;0.929350;,
  0.874054;-0.281135;0.396223;,
  0.256011;0.271237;0.927841;,
  0.486643;-0.774902;-0.403368;,
  0.486644;-0.774902;0.403366;,
  0.147555;-0.912022;-0.382679;,
  0.061120;-0.377775;-0.923878;,
  0.258671;-0.407546;-0.875783;,
  0.061121;-0.377776;0.923878;,
  0.147555;-0.912022;0.382678;,
  0.258672;-0.407547;0.875782;,
  -0.999990;0.004449;-0.000003;,
  -1.000000;0.000000;0.000000;,
  -0.999996;0.002860;0.000001;,
  0.920440;-0.002142;0.390877;,
  0.920440;-0.002142;-0.390877;,
  -0.999978;0.006674;-0.000009;,
  -0.999978;0.006673;-0.000003;,
  -0.999978;0.006673;0.000004;,
  -0.999978;0.006674;0.000009;;
  24;
  4;8,7,0,3;,
  4;2,2,4,4;,
  4;9,11,5,1;,
  3;20,21,22;,
  3;21,21,22;,
  3;21,21,22;,
  3;21,21,22;,
  4;23,10,6,24;,
  4;7,16,15,0;,
  4;10,13,12,6;,
  4;2,8,3,2;,
  4;17,19,9,1;,
  4;11,4,4,5;,
  4;6,7,8,24;,
  4;9,10,23,11;,
  4;13,18,14,12;,
  4;12,16,7,6;,
  3;25,20,26;,
  3;20,22,26;,
  3;26,22,27;,
  3;22,28,27;,
  4;19,13,10,9;,
  4;14,15,16,12;,
  4;17,18,13,19;;
 }
 MeshTextureCoords {
  36;
  0.393110;0.232500;,
  0.393110;0.136360;,
  0.625000;0.136360;,
  0.625000;0.231920;,
  0.375000;0.274990;,
  0.625000;0.275000;,
  0.625000;0.475000;,
  0.375000;0.475010;,
  0.393110;0.613640;,
  0.393110;0.517500;,
  0.625000;0.518080;,
  0.625000;0.613640;,
  0.875000;0.136360;,
  0.875000;0.231920;,
  0.850000;0.250000;,
  0.650000;0.250000;,
  0.150000;0.250000;,
  0.147560;0.134620;,
  0.353540;0.135410;,
  0.350000;0.250000;,
  0.404250;0.017920;,
  0.625000;0.013840;,
  0.145120;-0.000000;,
  0.354880;0.000000;,
  0.625000;0.736160;,
  0.404250;0.732080;,
  0.375320;0.613670;,
  0.375000;0.770120;,
  0.625000;0.770120;,
  0.625000;0.979880;,
  0.375000;0.979880;,
  0.875000;0.013840;,
  0.854880;0.000000;,
  0.645120;0.000000;,
  0.125000;0.016410;,
  0.125000;0.124870;;
 }
}