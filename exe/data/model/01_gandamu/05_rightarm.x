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
 69;
 -6.59725;-0.02448;-5.54669;,
 -6.59725;-0.02448;5.00591;,
 -4.76825;-0.02448;-7.37567;,
 -4.76825;-0.02448;6.83490;,
 5.78435;-0.02448;6.83490;,
 5.78435;-0.02448;-7.37567;,
 7.61337;-0.02448;5.00591;,
 7.61337;-0.02448;-5.54669;,
 -4.40675;-17.98645;6.57386;,
 -4.40675;-17.98645;-7.11463;,
 -2.44100;-17.98645;8.40285;,
 -2.44100;-17.98645;-8.94362;,
 3.45715;-17.98645;-8.94362;,
 3.45715;-17.98645;8.40285;,
 5.42288;-17.98645;-7.11463;,
 5.42288;-17.98645;6.57386;,
 -2.44100;-17.98645;-8.94362;,
 -4.40675;-17.98645;-7.11463;,
 -8.16518;-8.44360;-7.11405;,
 -6.27024;-8.44360;-8.94362;,
 -4.76825;-0.02448;-7.37567;,
 -4.40675;-17.98645;6.57386;,
 -2.44100;-17.98645;8.40285;,
 -6.27024;-8.44360;8.40285;,
 -8.16518;-8.44360;6.57325;,
 -4.76825;-0.02448;6.83490;,
 9.18133;-8.44360;-7.11405;,
 7.28638;-8.44360;-8.94362;,
 7.28638;-8.44360;-8.94362;,
 7.28638;-8.44360;8.40285;,
 9.18133;-8.44360;6.57325;,
 9.18133;-8.44360;6.57325;,
 7.28638;-8.44360;8.40285;,
 3.45715;-17.98645;8.40285;,
 5.42288;-17.98645;6.57386;,
 5.78435;-0.02448;6.83490;,
 7.28638;-8.44360;-8.94362;,
 5.78435;-0.02448;-7.37567;,
 3.45715;-17.98645;-8.94362;,
 -15.07468;-65.48266;13.54952;,
 -15.07468;-65.48266;-13.39290;,
 9.27125;-57.18561;-13.39290;,
 9.27125;-57.18561;13.54952;,
 -29.67767;-5.54900;-13.39290;,
 -29.67766;-5.54900;13.54952;,
 -27.29304;5.37985;13.54952;,
 -27.29304;5.37985;-13.39290;,
 -14.47804;-5.60920;13.54952;,
 -14.97673;-55.65669;13.54952;,
 9.27644;-55.74408;13.54952;,
 9.41566;-17.08718;13.54952;,
 9.27415;-56.37980;-13.39290;,
 9.27644;-55.74408;-13.39290;,
 9.41566;-17.08718;-13.39290;,
 -14.97673;-55.65669;-13.39290;,
 9.27644;-55.74408;-13.39290;,
 9.27415;-56.37980;-13.39290;,
 -29.58152;-55.60411;-13.39290;,
 -29.58151;-55.60411;13.54952;,
 -29.58152;-55.60411;-13.39290;,
 -29.58151;-55.60411;13.54952;,
 -27.29304;5.37985;-13.39290;,
 -17.71944;8.87263;-13.39290;,
 -14.47805;-5.60920;-13.39290;,
 -29.67767;-5.54900;-13.39290;,
 -17.71943;8.87263;13.54952;,
 -15.07468;-65.48266;13.54952;,
 9.27125;-57.18561;13.54952;,
 9.27125;-57.18561;-13.39290;;
 
 51;
 3;0,1,2;,
 3;1,3,2;,
 3;3,4,2;,
 3;2,4,5;,
 3;4,6,5;,
 3;6,7,5;,
 3;8,9,10;,
 3;9,11,10;,
 3;11,12,10;,
 3;10,12,13;,
 3;12,14,13;,
 3;14,15,13;,
 4;16,17,18,19;,
 4;19,18,0,20;,
 4;21,22,23,24;,
 4;24,23,25,1;,
 4;5,7,26,27;,
 4;28,26,14,12;,
 4;6,4,29,30;,
 4;31,32,33,34;,
 4;18,24,1,0;,
 4;26,7,6,30;,
 4;23,32,35,25;,
 4;36,19,20,37;,
 4;18,17,21,24;,
 4;23,22,33,32;,
 4;26,30,15,14;,
 4;36,38,16,19;,
 4;39,40,41,42;,
 4;43,44,45,46;,
 4;47,48,49,50;,
 3;51,52,49;,
 3;52,53,49;,
 3;53,50,49;,
 3;40,54,41;,
 3;54,55,41;,
 3;55,56,41;,
 4;57,58,44,43;,
 4;59,40,39,60;,
 3;59,54,40;,
 4;61,62,63,64;,
 4;45,65,62,61;,
 4;44,47,65,45;,
 4;58,48,47,44;,
 4;63,62,65,47;,
 4;53,63,47,50;,
 4;64,63,54,59;,
 4;55,54,63,53;,
 3;58,66,48;,
 4;49,48,66,67;,
 4;67,68,51,49;;
 
 MeshMaterialList {
  30;
  51;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  26,
  26,
  26,
  0,
  26,
  26,
  26,
  26,
  0,
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
  43;
  0.000000;-1.000000;-0.000000;,
  -0.918245;-0.054984;-0.392178;,
  -0.369174;0.047194;-0.928161;,
  -0.918245;-0.054984;0.392176;,
  -0.369176;0.047194;0.928161;,
  0.000000;1.000000;0.000000;,
  0.000000;1.000000;0.000000;,
  0.918244;-0.054983;-0.392179;,
  0.369173;0.047195;-0.928162;,
  0.369175;0.047195;0.928161;,
  0.918245;-0.054983;0.392177;,
  -0.883533;-0.468368;0.000000;,
  0.322580;-0.946542;-0.000000;,
  -0.753190;0.657803;0.000000;,
  -0.994339;0.106253;0.000000;,
  0.000000;0.000000;1.000000;,
  0.999994;-0.003601;-0.000000;,
  -0.134282;-0.990943;0.000000;,
  0.000000;0.000000;-1.000000;,
  -0.342737;0.939431;0.000000;,
  0.999994;-0.003601;-0.000000;,
  0.999994;-0.003600;-0.000000;,
  -0.359853;-0.143038;-0.921979;,
  -0.860913;-0.340374;-0.378119;,
  -0.897567;0.235173;-0.372917;,
  -0.365166;0.234367;-0.900959;,
  -0.860914;-0.340374;0.378117;,
  -0.359855;-0.143038;0.921978;,
  -0.365168;0.234367;0.900958;,
  -0.897568;0.235172;0.372915;,
  0.365164;0.234368;-0.900959;,
  0.897566;0.235176;-0.372919;,
  0.860913;-0.340375;-0.378118;,
  0.359854;-0.143039;-0.921979;,
  0.897567;0.235176;0.372916;,
  0.365166;0.234368;0.900958;,
  0.359856;-0.143039;0.921978;,
  0.860914;-0.340375;0.378116;,
  0.999994;-0.003601;-0.000000;,
  0.782838;0.622226;-0.000000;,
  0.975855;0.218420;-0.000000;,
  0.433007;0.901391;-0.000000;,
  0.999994;-0.003599;-0.000000;;
  51;
  3;5,5,5;,
  3;5,5,5;,
  3;5,5,5;,
  3;5,5,5;,
  3;5,5,5;,
  3;5,6,5;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  4;22,23,1,2;,
  4;2,1,24,25;,
  4;26,27,4,3;,
  4;3,4,28,29;,
  4;30,31,7,8;,
  4;8,7,32,33;,
  4;34,35,9,10;,
  4;10,9,36,37;,
  4;1,3,29,24;,
  4;7,31,34,10;,
  4;4,9,35,28;,
  4;8,2,25,30;,
  4;1,23,26,3;,
  4;4,27,36,9;,
  4;7,10,37,32;,
  4;8,33,22,2;,
  4;17,17,12,12;,
  4;14,14,13,13;,
  4;15,15,15,15;,
  3;21,20,38;,
  3;20,16,38;,
  3;16,16,38;,
  3;18,18,18;,
  3;18,18,18;,
  3;15,15,15;,
  4;11,11,14,14;,
  4;11,17,17,11;,
  3;18,18,18;,
  4;18,18,18,18;,
  4;13,19,19,13;,
  4;15,15,15,15;,
  4;15,15,15,15;,
  4;39,40,40,39;,
  4;41,39,39,41;,
  4;18,18,18,18;,
  4;18,18,18,18;,
  3;15,15,15;,
  4;15,15,15,15;,
  4;42,42,21,38;;
 }
 MeshTextureCoords {
  69;
  0.407180;0.250000;,
  0.592820;0.250000;,
  0.375000;0.282180;,
  0.625000;0.282180;,
  0.625000;0.467820;,
  0.375000;0.467820;,
  0.592820;0.500000;,
  0.407180;0.500000;,
  0.598640;1.000000;,
  0.401360;1.000000;,
  0.625000;0.950000;,
  0.375000;0.950000;,
  0.375000;0.800000;,
  0.625000;0.800000;,
  0.401360;0.750000;,
  0.598640;0.750000;,
  0.325000;0.000000;,
  0.401360;0.000000;,
  0.401370;0.128660;,
  0.347690;0.128660;,
  0.342820;0.250000;,
  0.598640;0.000000;,
  0.675000;0.000000;,
  0.652310;0.128660;,
  0.598630;0.128660;,
  0.657180;0.250000;,
  0.401370;0.621340;,
  0.375000;0.615900;,
  0.375000;0.630050;,
  0.625000;0.616440;,
  0.598630;0.621340;,
  0.875000;0.128660;,
  0.847690;0.128660;,
  0.825000;0.000000;,
  0.875000;0.000000;,
  0.842820;0.250000;,
  0.152310;0.128660;,
  0.157180;0.250000;,
  0.175000;0.000000;,
  0.471920;1.000000;,
  0.471920;0.750000;,
  0.625000;0.750000;,
  0.625000;1.000000;,
  0.125000;0.194130;,
  0.375000;0.194130;,
  0.375000;0.250000;,
  0.125000;0.250000;,
  0.471920;0.194130;,
  0.471920;0.031860;,
  0.625000;0.006980;,
  0.625000;0.194130;,
  0.872490;0.007540;,
  0.870510;0.013480;,
  0.750000;0.375000;,
  0.471920;0.718140;,
  0.629490;0.736520;,
  0.627510;0.742460;,
  0.125000;0.000000;,
  0.375000;0.000000;,
  0.375000;0.750000;,
  0.375000;1.000000;,
  0.375000;0.500000;,
  0.471920;0.500000;,
  0.471920;0.555870;,
  0.375000;0.555870;,
  0.471920;0.250000;,
  0.471920;0.000000;,
  0.625000;0.000000;,
  0.875000;0.000000;;
 }
}