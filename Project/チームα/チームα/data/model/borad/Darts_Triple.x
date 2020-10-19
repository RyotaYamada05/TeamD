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
 160;
 -314.22610;-24.78303;0.00000;,
 -311.31750;-49.36089;0.00001;,
 -265.88229;-42.16446;0.00000;,
 -268.36630;-21.17374;-0.00001;,
 -306.48871;-73.63448;0.00000;,
 -261.75851;-62.89549;0.00001;,
 -299.77130;-97.45460;0.00000;,
 -256.02121;-83.23924;0.00001;,
 -291.20459;-120.67418;0.00003;,
 -248.70490;-103.07003;-0.00001;,
 -280.84311;-143.14986;0.00003;,
 -239.85590;-122.26575;0.00003;,
 -268.75031;-164.74388;0.00003;,
 -229.52730;-140.70810;-0.00003;,
 -255.00101;-185.32196;0.00001;,
 -217.78450;-158.28300;0.00002;,
 -239.67850;-204.75748;-0.00001;,
 -204.69870;-174.88222;0.00004;,
 -222.87880;-222.93233;0.00003;,
 -190.35060;-190.40417;-0.00002;,
 -204.70441;-239.73206;0.00000;,
 -174.82910;-204.75163;-0.00005;,
 -185.26880;-255.05417;0.00005;,
 -158.22980;-217.83791;-0.00001;,
 -164.69040;-268.80338;0.00001;,
 -140.65469;-229.58147;0.00002;,
 -143.09680;-280.89688;-0.00004;,
 -122.21250;-239.90950;0.00001;,
 -120.62070;-291.25873;0.00007;,
 -103.01690;-248.75871;0.00002;,
 -97.40130;-299.82495;0.00003;,
 -83.18600;-256.07437;0.00002;,
 -73.58120;-306.54337;0.00002;,
 -62.84250;-261.81201;0.00008;,
 -49.30760;-311.37073;0.00006;,
 -42.11130;-265.93594;0.00003;,
 -24.73000;-314.28027;0.00001;,
 -21.12070;-268.42020;0.00004;,
 0.00030;-315.25235;0.00002;,
 0.00030;-269.24994;0.00003;,
 24.73040;-314.28027;0.00001;,
 21.12120;-268.42020;0.00004;,
 49.30820;-311.37082;0.00004;,
 42.11200;-265.93594;0.00003;,
 73.58190;-306.54337;0.00002;,
 62.84310;-261.81247;0.00002;,
 97.40190;-299.82510;0.00002;,
 83.18670;-256.07471;-0.00000;,
 120.62160;-291.25885;0.00002;,
 103.01740;-248.75896;0.00007;,
 143.09740;-280.89697;0.00001;,
 122.21320;-239.90950;0.00001;,
 164.69119;-268.80338;0.00001;,
 140.65530;-229.58147;0.00002;,
 185.26920;-255.05443;-0.00002;,
 158.23039;-217.83827;-0.00002;,
 204.70551;-239.73276;0.00002;,
 174.82961;-204.75177;-0.00002;,
 222.87950;-222.93242;-0.00000;,
 190.35159;-190.40440;0.00006;,
 239.67979;-204.75839;0.00001;,
 204.69901;-174.88246;-0.00003;,
 255.00150;-185.32243;0.00002;,
 217.78529;-158.28378;0.00001;,
 268.75049;-164.74409;0.00003;,
 229.52890;-140.70810;-0.00003;,
 280.84409;-143.15019;0.00002;,
 239.85651;-122.26608;-0.00002;,
 291.20581;-120.67453;-0.00002;,
 248.70621;-103.07037;0.00002;,
 299.77209;-97.45483;0.00000;,
 256.02179;-83.23952;0.00000;,
 306.49030;-73.63458;0.00001;,
 261.75961;-62.89579;0.00000;,
 311.31781;-49.36097;-0.00000;,
 265.88290;-42.16477;0.00000;,
 314.22760;-24.78313;0.00000;,
 268.36749;-21.17393;0.00000;,
 315.19940;-0.05300;0.00000;,
 269.19769;-0.05300;0.00000;,
 314.22760;24.67733;-0.00001;,
 268.36749;21.06804;-0.00000;,
 311.31781;49.25496;0.00000;,
 265.88290;42.05877;-0.00000;,
 306.49060;73.52866;-0.00000;,
 261.75961;62.78998;0.00000;,
 299.77219;97.34885;-0.00001;,
 256.02209;83.13352;-0.00001;,
 291.20599;120.56815;-0.00003;,
 248.70641;102.96452;-0.00001;,
 280.84421;143.04439;0.00001;,
 239.85651;122.16018;-0.00001;,
 268.75079;164.63806;-0.00001;,
 229.52921;140.60251;0.00001;,
 255.00160;185.21651;-0.00004;,
 217.78580;158.17740;0.00004;,
 239.67990;204.65216;0.00003;,
 204.69960;174.77690;-0.00004;,
 222.87950;222.82674;-0.00002;,
 190.35181;190.29851;0.00001;,
 204.70610;239.62645;-0.00003;,
 174.82970;204.64635;0.00002;,
 185.26961;254.94894;-0.00003;,
 158.23090;217.73238;-0.00003;,
 164.69141;268.69815;-0.00001;,
 140.65570;229.47520;0.00002;,
 143.09760;280.79135;-0.00002;,
 122.21330;239.80391;-0.00002;,
 120.62180;291.15326;-0.00003;,
 103.01790;248.65327;-0.00002;,
 97.40220;299.71957;-0.00003;,
 83.18690;255.96904;-0.00004;,
 73.58210;306.43665;-0.00003;,
 62.84340;261.70663;-0.00005;,
 49.30840;311.26550;-0.00006;,
 42.11220;265.83063;-0.00001;,
 24.73050;314.17487;-0.00002;,
 21.12140;268.31479;-0.00003;,
 0.00040;315.14691;-0.00005;,
 0.00040;269.14459;-0.00003;,
 -24.72980;314.17487;-0.00002;,
 -21.12060;268.31497;-0.00004;,
 -49.30760;311.26550;-0.00006;,
 -42.11130;265.83072;-0.00003;,
 -73.58120;306.43674;-0.00002;,
 -62.84250;261.70663;-0.00005;,
 -97.40140;299.71973;-0.00003;,
 -83.18600;255.96904;-0.00004;,
 -120.62090;291.15350;-0.00007;,
 -103.01700;248.65334;-0.00002;,
 -143.09689;280.79135;-0.00002;,
 -122.21280;239.80431;-0.00001;,
 -164.69060;268.69815;-0.00001;,
 -140.65500;229.47528;0.00000;,
 -185.26910;254.94897;-0.00005;,
 -158.22980;217.73271;0.00001;,
 -204.70461;239.62686;-0.00000;,
 -174.82930;204.64644;0.00005;,
 -222.87910;222.82701;0.00002;,
 -190.35091;190.29875;0.00000;,
 -239.67909;204.65228;0.00001;,
 -204.69890;174.77702;-0.00004;,
 -255.00130;185.21677;-0.00001;,
 -217.78470;158.17740;0.00004;,
 -268.75049;164.63841;-0.00003;,
 -229.52760;140.60258;-0.00004;,
 -280.84351;143.04456;0.00002;,
 -239.85651;122.16048;-0.00001;,
 -291.20541;120.56866;-0.00001;,
 -248.70570;102.96464;-0.00001;,
 -299.77191;97.34928;-0.00003;,
 -256.02139;83.13373;-0.00000;,
 -306.49030;73.52899;-0.00002;,
 -261.75900;62.79008;0.00000;,
 -311.31769;49.25527;-0.00001;,
 -265.88300;42.05887;-0.00000;,
 -314.22720;24.67733;-0.00001;,
 -268.36719;21.06814;0.00000;,
 -315.19919;-0.05290;0.00000;,
 -269.19681;-0.05290;0.00000;;
 
 80;
 4;0,1,2,3;,
 4;1,4,5,2;,
 4;4,6,7,5;,
 4;6,8,9,7;,
 4;8,10,11,9;,
 4;10,12,13,11;,
 4;12,14,15,13;,
 4;14,16,17,15;,
 4;16,18,19,17;,
 4;18,20,21,19;,
 4;20,22,23,21;,
 4;22,24,25,23;,
 4;24,26,27,25;,
 4;26,28,29,27;,
 4;28,30,31,29;,
 4;30,32,33,31;,
 4;32,34,35,33;,
 4;34,36,37,35;,
 4;36,38,39,37;,
 4;38,40,41,39;,
 4;40,42,43,41;,
 4;42,44,45,43;,
 4;44,46,47,45;,
 4;46,48,49,47;,
 4;48,50,51,49;,
 4;50,52,53,51;,
 4;52,54,55,53;,
 4;54,56,57,55;,
 4;56,58,59,57;,
 4;58,60,61,59;,
 4;60,62,63,61;,
 4;62,64,65,63;,
 4;64,66,67,65;,
 4;66,68,69,67;,
 4;68,70,71,69;,
 4;70,72,73,71;,
 4;72,74,75,73;,
 4;74,76,77,75;,
 4;76,78,79,77;,
 4;78,80,81,79;,
 4;80,82,83,81;,
 4;82,84,85,83;,
 4;84,86,87,85;,
 4;86,88,89,87;,
 4;88,90,91,89;,
 4;90,92,93,91;,
 4;92,94,95,93;,
 4;94,96,97,95;,
 4;96,98,99,97;,
 4;98,100,101,99;,
 4;100,102,103,101;,
 4;102,104,105,103;,
 4;104,106,107,105;,
 4;106,108,109,107;,
 4;108,110,111,109;,
 4;110,112,113,111;,
 4;112,114,115,113;,
 4;114,116,117,115;,
 4;116,118,119,117;,
 4;118,120,121,119;,
 4;120,122,123,121;,
 4;122,124,125,123;,
 4;124,126,127,125;,
 4;126,128,129,127;,
 4;128,130,131,129;,
 4;130,132,133,131;,
 4;132,134,135,133;,
 4;134,136,137,135;,
 4;136,138,139,137;,
 4;138,140,141,139;,
 4;140,142,143,141;,
 4;142,144,145,143;,
 4;144,146,147,145;,
 4;146,148,149,147;,
 4;148,150,151,149;,
 4;150,152,153,151;,
 4;152,154,155,153;,
 4;154,156,157,155;,
 4;156,158,159,157;,
 4;158,0,3,159;;
 
 MeshMaterialList {
  5;
  80;
  3,
  2,
  2,
  2,
  2,
  3,
  3,
  3,
  3,
  2,
  2,
  2,
  2,
  3,
  3,
  3,
  3,
  2,
  2,
  2,
  2,
  3,
  3,
  3,
  3,
  2,
  2,
  2,
  2,
  3,
  3,
  3,
  3,
  2,
  2,
  2,
  2,
  3,
  3,
  3,
  3,
  2,
  2,
  2,
  2,
  3,
  3,
  3,
  3,
  2,
  2,
  2,
  2,
  3,
  3,
  3,
  3,
  2,
  2,
  2,
  2,
  3,
  3,
  3,
  3,
  2,
  2,
  2,
  2,
  3,
  3,
  3,
  3,
  2,
  2,
  2,
  2,
  3,
  3,
  3;;
  Material {
   0.400000;0.400000;0.400000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.103200;0.103200;0.103200;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.000000;0.100000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.019200;0.050400;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  80;
  0.000000;0.000000;1.000000;,
  0.000000;0.000000;1.000000;,
  -0.000000;-0.000000;1.000000;,
  0.000000;0.000000;1.000000;,
  0.000000;0.000001;1.000000;,
  0.000001;0.000000;1.000000;,
  0.000001;-0.000000;1.000000;,
  -0.000000;0.000000;1.000000;,
  -0.000000;-0.000000;1.000000;,
  0.000001;-0.000000;1.000000;,
  0.000000;0.000001;1.000000;,
  -0.000000;0.000001;1.000000;,
  0.000001;-0.000000;1.000000;,
  -0.000001;-0.000000;1.000000;,
  -0.000001;0.000001;1.000000;,
  -0.000000;0.000000;1.000000;,
  -0.000000;-0.000000;1.000000;,
  0.000000;-0.000000;1.000000;,
  0.000000;-0.000000;1.000000;,
  0.000000;-0.000001;1.000000;,
  -0.000000;-0.000000;1.000000;,
  0.000000;-0.000000;1.000000;,
  0.000001;0.000000;1.000000;,
  -0.000000;-0.000000;1.000000;,
  0.000000;-0.000000;1.000000;,
  0.000001;-0.000000;1.000000;,
  0.000001;0.000000;1.000000;,
  0.000000;0.000000;1.000000;,
  -0.000001;-0.000001;1.000000;,
  0.000000;0.000000;1.000000;,
  0.000000;0.000000;1.000000;,
  -0.000001;0.000000;1.000000;,
  -0.000001;0.000001;1.000000;,
  -0.000000;0.000000;1.000000;,
  0.000000;-0.000000;1.000000;,
  0.000000;-0.000000;1.000000;,
  -0.000000;0.000000;1.000000;,
  0.000000;0.000000;1.000000;,
  0.000000;0.000000;1.000000;,
  0.000000;0.000000;1.000000;,
  0.000000;0.000000;1.000000;,
  -0.000000;-0.000000;1.000000;,
  -0.000000;0.000000;1.000000;,
  0.000000;0.000000;1.000000;,
  0.000000;-0.000000;1.000000;,
  0.000000;-0.000000;1.000000;,
  0.000000;0.000000;1.000000;,
  0.000000;0.000001;1.000000;,
  -0.000000;0.000000;1.000000;,
  0.000000;0.000000;1.000000;,
  0.000000;0.000001;1.000000;,
  0.000000;0.000000;1.000000;,
  0.000000;0.000000;1.000000;,
  -0.000000;0.000000;1.000000;,
  -0.000000;0.000000;1.000000;,
  -0.000000;-0.000000;1.000000;,
  0.000000;0.000000;1.000000;,
  0.000000;0.000000;1.000000;,
  -0.000000;0.000000;1.000000;,
  -0.000000;0.000000;1.000000;,
  -0.000000;-0.000000;1.000000;,
  -0.000000;0.000000;1.000000;,
  0.000000;-0.000000;1.000000;,
  -0.000000;0.000000;1.000000;,
  0.000000;0.000001;1.000000;,
  0.000001;0.000001;1.000000;,
  -0.000000;0.000000;1.000000;,
  -0.000000;0.000001;1.000000;,
  0.000000;0.000001;1.000000;,
  -0.000000;-0.000001;1.000000;,
  0.000000;-0.000000;1.000000;,
  -0.000000;-0.000000;1.000000;,
  -0.000000;-0.000000;1.000000;,
  0.000001;0.000000;1.000000;,
  -0.000000;-0.000000;1.000000;,
  -0.000000;0.000000;1.000000;,
  -0.000000;0.000000;1.000000;,
  -0.000000;0.000000;1.000000;,
  -0.000000;0.000000;1.000000;,
  0.000000;-0.000000;1.000000;;
  80;
  4;0,1,1,0;,
  4;1,2,2,1;,
  4;2,3,3,2;,
  4;3,4,4,3;,
  4;4,5,5,4;,
  4;5,6,6,5;,
  4;6,7,7,6;,
  4;7,8,8,7;,
  4;8,9,9,8;,
  4;9,10,10,9;,
  4;10,11,11,10;,
  4;11,12,12,11;,
  4;12,13,13,12;,
  4;13,14,14,13;,
  4;14,15,15,14;,
  4;15,16,16,15;,
  4;16,17,17,16;,
  4;17,18,18,17;,
  4;18,19,19,18;,
  4;19,20,20,19;,
  4;20,21,21,20;,
  4;21,22,22,21;,
  4;22,23,23,22;,
  4;23,24,24,23;,
  4;24,25,25,24;,
  4;25,26,26,25;,
  4;26,27,27,26;,
  4;27,28,28,27;,
  4;28,29,29,28;,
  4;29,30,30,29;,
  4;30,31,31,30;,
  4;31,32,32,31;,
  4;32,33,33,32;,
  4;33,34,34,33;,
  4;34,35,35,34;,
  4;35,36,36,35;,
  4;36,37,37,36;,
  4;37,38,38,37;,
  4;38,39,39,38;,
  4;39,40,40,39;,
  4;40,41,41,40;,
  4;41,42,42,41;,
  4;42,43,43,42;,
  4;43,44,44,43;,
  4;44,45,45,44;,
  4;45,46,46,45;,
  4;46,47,47,46;,
  4;47,48,48,47;,
  4;48,49,49,48;,
  4;49,50,50,49;,
  4;50,51,51,50;,
  4;51,52,52,51;,
  4;52,53,53,52;,
  4;53,54,54,53;,
  4;54,55,55,54;,
  4;55,56,56,55;,
  4;56,57,57,56;,
  4;57,58,58,57;,
  4;58,59,59,58;,
  4;59,60,60,59;,
  4;60,61,61,60;,
  4;61,62,62,61;,
  4;62,63,63,62;,
  4;63,64,64,63;,
  4;64,65,65,64;,
  4;65,66,66,65;,
  4;66,67,67,66;,
  4;67,68,68,67;,
  4;68,69,69,68;,
  4;69,70,70,69;,
  4;70,71,71,70;,
  4;71,72,72,71;,
  4;72,73,73,72;,
  4;73,74,74,73;,
  4;74,75,75,74;,
  4;75,76,76,75;,
  4;76,77,77,76;,
  4;77,78,78,77;,
  4;78,79,79,78;,
  4;79,0,0,79;;
 }
 MeshTextureCoords {
  160;
  0.603850;0.851920;,
  0.602880;0.860050;,
  0.577160;0.855970;,
  0.577880;0.849880;,
  0.601290;0.868070;,
  0.575970;0.861990;,
  0.599070;0.875940;,
  0.574300;0.867890;,
  0.596240;0.883610;,
  0.572180;0.873650;,
  0.592810;0.891040;,
  0.569610;0.879220;,
  0.588820;0.898180;,
  0.566610;0.884570;,
  0.584270;0.904980;,
  0.563200;0.889670;,
  0.579210;0.911400;,
  0.559410;0.894490;,
  0.573660;0.917410;,
  0.555240;0.898990;,
  0.567650;0.922960;,
  0.550740;0.903160;,
  0.561230;0.928020;,
  0.545920;0.906950;,
  0.554430;0.932570;,
  0.540820;0.910360;,
  0.547290;0.936560;,
  0.535470;0.913360;,
  0.539860;0.939990;,
  0.529900;0.915930;,
  0.532190;0.942820;,
  0.524140;0.918050;,
  0.524320;0.945040;,
  0.518240;0.919720;,
  0.516300;0.946630;,
  0.512220;0.920910;,
  0.508170;0.947600;,
  0.506130;0.921630;,
  0.500000;0.947920;,
  0.500000;0.921880;,
  0.491830;0.947600;,
  0.493870;0.921630;,
  0.483710;0.946630;,
  0.487780;0.920910;,
  0.475680;0.945040;,
  0.481760;0.919720;,
  0.467810;0.942820;,
  0.475860;0.918050;,
  0.460140;0.939990;,
  0.470100;0.915930;,
  0.452710;0.936560;,
  0.464530;0.913360;,
  0.445570;0.932570;,
  0.459180;0.910360;,
  0.438770;0.928020;,
  0.454080;0.906950;,
  0.432350;0.922960;,
  0.449260;0.903160;,
  0.426340;0.917410;,
  0.444760;0.898990;,
  0.420790;0.911400;,
  0.440590;0.894490;,
  0.415730;0.904980;,
  0.436800;0.889670;,
  0.411180;0.898180;,
  0.433390;0.884570;,
  0.407190;0.891040;,
  0.430390;0.879220;,
  0.403760;0.883610;,
  0.427820;0.873650;,
  0.400930;0.875940;,
  0.425700;0.867890;,
  0.398710;0.868070;,
  0.424030;0.861990;,
  0.397120;0.860050;,
  0.422840;0.855970;,
  0.396150;0.851920;,
  0.422120;0.849880;,
  0.395830;0.843750;,
  0.421880;0.843750;,
  0.396150;0.835580;,
  0.422120;0.837620;,
  0.397120;0.827450;,
  0.422840;0.831530;,
  0.398710;0.819430;,
  0.424030;0.825510;,
  0.400930;0.811560;,
  0.425700;0.819610;,
  0.403760;0.803890;,
  0.427820;0.813850;,
  0.407190;0.796460;,
  0.430390;0.808280;,
  0.411180;0.789320;,
  0.433390;0.802930;,
  0.415730;0.782520;,
  0.436800;0.797830;,
  0.420790;0.776100;,
  0.440590;0.793010;,
  0.426340;0.770090;,
  0.444760;0.788510;,
  0.432350;0.764540;,
  0.449260;0.784340;,
  0.438770;0.759480;,
  0.454080;0.780550;,
  0.445570;0.754930;,
  0.459180;0.777140;,
  0.452710;0.750940;,
  0.464530;0.774140;,
  0.460140;0.747510;,
  0.470100;0.771570;,
  0.467810;0.744680;,
  0.475860;0.769450;,
  0.475680;0.742460;,
  0.481760;0.767780;,
  0.483710;0.740870;,
  0.487780;0.766590;,
  0.491830;0.739900;,
  0.493870;0.765870;,
  0.500000;0.739580;,
  0.500000;0.765620;,
  0.508170;0.739900;,
  0.506130;0.765870;,
  0.516300;0.740870;,
  0.512220;0.766590;,
  0.524320;0.742460;,
  0.518240;0.767780;,
  0.532190;0.744680;,
  0.524140;0.769450;,
  0.539860;0.747510;,
  0.529900;0.771570;,
  0.547290;0.750940;,
  0.535470;0.774140;,
  0.554430;0.754930;,
  0.540820;0.777140;,
  0.561230;0.759480;,
  0.545920;0.780550;,
  0.567650;0.764540;,
  0.550740;0.784340;,
  0.573660;0.770090;,
  0.555240;0.788510;,
  0.579210;0.776100;,
  0.559410;0.793010;,
  0.584270;0.782520;,
  0.563200;0.797830;,
  0.588820;0.789320;,
  0.566610;0.802930;,
  0.592810;0.796460;,
  0.569610;0.808280;,
  0.596240;0.803890;,
  0.572180;0.813850;,
  0.599070;0.811560;,
  0.574300;0.819610;,
  0.601290;0.819430;,
  0.575970;0.825510;,
  0.602880;0.827450;,
  0.577160;0.831530;,
  0.603850;0.835580;,
  0.577880;0.837620;,
  0.604170;0.843750;,
  0.578120;0.843750;;
 }
}
