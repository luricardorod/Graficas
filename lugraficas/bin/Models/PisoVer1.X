xof 0303txt 0032
template KeyValuePair {
 <26e6b1c3-3d4d-4a1d-a437-b33668ffa1c2>
 STRING key;
 STRING value;
}

template Frame {
 <3d82ab46-62da-11cf-ab39-0020af71e433>
 [...]
}

template Matrix4x4 {
 <f6f23f45-7686-11cf-8f52-0040333594a3>
 array FLOAT matrix[16];
}

template FrameTransformMatrix {
 <f6f23f41-7686-11cf-8f52-0040333594a3>
 Matrix4x4 frameMatrix;
}

template ObjectMatrixComment {
 <95a48e28-7ef4-4419-a16a-ba9dbdf0d2bc>
 Matrix4x4 objectMatrix;
}

template Vector {
 <3d82ab5e-62da-11cf-ab39-0020af71e433>
 FLOAT x;
 FLOAT y;
 FLOAT z;
}

template MeshFace {
 <3d82ab5f-62da-11cf-ab39-0020af71e433>
 DWORD nFaceVertexIndices;
 array DWORD faceVertexIndices[nFaceVertexIndices];
}

template Mesh {
 <3d82ab44-62da-11cf-ab39-0020af71e433>
 DWORD nVertices;
 array Vector vertices[nVertices];
 DWORD nFaces;
 array MeshFace faces[nFaces];
 [...]
}

template MeshNormals {
 <f6f23f43-7686-11cf-8f52-0040333594a3>
 DWORD nNormals;
 array Vector normals[nNormals];
 DWORD nFaceNormals;
 array MeshFace faceNormals[nFaceNormals];
}

template Coords2d {
 <f6f23f44-7686-11cf-8f52-0040333594a3>
 FLOAT u;
 FLOAT v;
}

template MeshTextureCoords {
 <f6f23f40-7686-11cf-8f52-0040333594a3>
 DWORD nTextureCoords;
 array Coords2d textureCoords[nTextureCoords];
}

template VertexElement {
 <f752461c-1e23-48f6-b9f8-8350850f336f>
 DWORD Type;
 DWORD Method;
 DWORD Usage;
 DWORD UsageIndex;
}

template DeclData {
 <bf22e553-292c-4781-9fea-62bd554bdd93>
 DWORD nElements;
 array VertexElement Elements[nElements];
 DWORD nDWords;
 array DWORD data[nDWords];
}

template ColorRGBA {
 <35ff44e0-6c7c-11cf-8f52-0040333594a3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
 FLOAT alpha;
}

template ColorRGB {
 <d3e16e81-7835-11cf-8f52-0040333594a3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
}

template Material {
 <3d82ab4d-62da-11cf-ab39-0020af71e433>
 ColorRGBA faceColor;
 FLOAT power;
 ColorRGB specularColor;
 ColorRGB emissiveColor;
 [...]
}

template MeshMaterialList {
 <f6f23f42-7686-11cf-8f52-0040333594a3>
 DWORD nMaterials;
 DWORD nFaceIndexes;
 array DWORD faceIndexes[nFaceIndexes];
 [Material <3d82ab4d-62da-11cf-ab39-0020af71e433>]
}

template EffectInstance {
 <e331f7e4-0559-4cc2-8e99-1cec1657928f>
 STRING EffectFilename;
 [...]
}

template EffectParamDWord {
 <e13963bc-ae51-4c5d-b00f-cfa3a9d97ce5>
 STRING ParamName;
 DWORD Value;
}

template EffectParamFloats {
 <3014b9a0-62f5-478c-9b86-e4ac9f4e418b>
 STRING ParamName;
 DWORD nFloats;
 array FLOAT Floats[nFloats];
}

template EffectParamString {
 <1dbc4c88-94c1-46ee-9076-2c28818c9481>
 STRING ParamName;
 STRING Value;
}

template TextureFilename {
 <a42790e1-7810-11cf-8f52-0040333594a3>
 STRING filename;
}


KeyValuePair {
 "Date";
 "2017-08-16 11:03:51";
}

KeyValuePair {
 "File";
 "";
}

KeyValuePair {
 "User";
 "F_A_R";
}

KeyValuePair {
 "CoreTime";
 "0";
}

Frame pPlane13 {
 

 FrameTransformMatrix relative {
  0.010000,0.000000,0.000000,0.000000,0.000000,0.010000,0.000000,0.000000,0.000000,-0.000000,0.010000,0.000000,0.000000,0.000000,0.000000,1.000000;;
 }

 ObjectMatrixComment object {
  0.010000,0.000000,0.000000,0.000000,0.000000,0.010000,0.000000,0.000000,0.000000,-0.000000,0.010000,0.000000,0.000000,0.000000,0.000000,1.000000;;
 }

 Mesh mesh_pPlane13 {
  25;
  -1.250000;-0.000000;1.250000;,
  -0.625000;-0.000000;1.250000;,
  -0.625000;-0.000000;0.625000;,
  -1.250000;-0.000000;0.625000;,
  0.000000;-0.000000;1.250000;,
  0.000000;-0.000000;0.625000;,
  -0.625000;0.000000;0.000000;,
  -1.250000;0.000000;0.000000;,
  0.000000;0.000000;0.000000;,
  0.625000;-0.000000;1.250000;,
  1.250000;-0.000000;1.250000;,
  1.250000;-0.000000;0.625000;,
  0.625000;-0.000000;0.625000;,
  1.250000;0.000000;0.000000;,
  0.625000;0.000000;0.000000;,
  1.250000;0.000000;-1.250000;,
  0.625000;0.000000;-1.250000;,
  0.625000;0.000000;-0.625000;,
  1.250000;0.000000;-0.625000;,
  0.000000;0.000000;-1.250000;,
  0.000000;0.000000;-0.625000;,
  -0.625000;0.000000;-1.250000;,
  -1.250000;0.000000;-1.250000;,
  -1.250000;0.000000;-0.625000;,
  -0.625000;0.000000;-0.625000;;
  32;
  3;0,1,2;,
  3;2,3,0;,
  3;1,4,5;,
  3;5,2,1;,
  3;3,2,6;,
  3;6,7,3;,
  3;2,5,8;,
  3;8,6,2;,
  3;9,10,11;,
  3;11,12,9;,
  3;12,11,13;,
  3;13,14,12;,
  3;4,9,12;,
  3;12,5,4;,
  3;5,12,14;,
  3;14,8,5;,
  3;15,16,17;,
  3;17,18,15;,
  3;16,19,20;,
  3;20,17,16;,
  3;18,17,14;,
  3;14,13,18;,
  3;17,20,8;,
  3;8,14,17;,
  3;21,22,23;,
  3;23,24,21;,
  3;24,23,7;,
  3;7,6,24;,
  3;19,21,24;,
  3;24,20,19;,
  3;20,24,6;,
  3;6,8,20;;

  MeshNormals normals {
   25;
   0.000000;1.000000;0.000000;,
   0.000000;1.000000;0.000000;,
   0.000000;1.000000;0.000000;,
   0.000000;1.000000;0.000000;,
   0.000000;1.000000;0.000000;,
   0.000000;1.000000;0.000000;,
   0.000000;1.000000;0.000000;,
   0.000000;1.000000;0.000000;,
   0.000000;1.000000;0.000000;,
   0.000000;1.000000;0.000000;,
   0.000000;1.000000;0.000000;,
   0.000000;1.000000;0.000000;,
   0.000000;1.000000;0.000000;,
   0.000000;1.000000;0.000000;,
   0.000000;1.000000;0.000000;,
   0.000000;1.000000;0.000000;,
   0.000000;1.000000;0.000000;,
   0.000000;1.000000;0.000000;,
   0.000000;1.000000;0.000000;,
   0.000000;1.000000;0.000000;,
   0.000000;1.000000;0.000000;,
   0.000000;1.000000;0.000000;,
   0.000000;1.000000;0.000000;,
   0.000000;1.000000;0.000000;,
   0.000000;1.000000;0.000000;;
   32;
   3;0,1,2;,
   3;2,3,0;,
   3;1,4,5;,
   3;5,2,1;,
   3;3,2,6;,
   3;6,7,3;,
   3;2,5,8;,
   3;8,6,2;,
   3;9,10,11;,
   3;11,12,9;,
   3;12,11,13;,
   3;13,14,12;,
   3;4,9,12;,
   3;12,5,4;,
   3;5,12,14;,
   3;14,8,5;,
   3;15,16,17;,
   3;17,18,15;,
   3;16,19,20;,
   3;20,17,16;,
   3;18,17,14;,
   3;14,13,18;,
   3;17,20,8;,
   3;8,14,17;,
   3;21,22,23;,
   3;23,24,21;,
   3;24,23,7;,
   3;7,6,24;,
   3;19,21,24;,
   3;24,20,19;,
   3;20,24,6;,
   3;6,8,20;;
  }

  MeshTextureCoords tc0 {
   25;
   0.048638;0.456000;,
   0.093914;0.456000;,
   0.093914;0.410725;,
   0.048638;0.410725;,
   0.139190;0.456000;,
   0.139190;0.410725;,
   0.093914;0.365449;,
   0.048638;0.365449;,
   0.139190;0.365449;,
   0.184466;0.456000;,
   0.229742;0.456000;,
   0.229742;0.410725;,
   0.184466;0.410725;,
   0.229742;0.365449;,
   0.184466;0.365449;,
   0.229742;0.274897;,
   0.184466;0.274897;,
   0.184466;0.320173;,
   0.229742;0.320173;,
   0.139190;0.274897;,
   0.139190;0.320173;,
   0.093914;0.274897;,
   0.048638;0.274897;,
   0.048638;0.320173;,
   0.093914;0.320173;;
  }

  DeclData {
   2;
   2;0;7;0;,
   2;0;6;0;;
   150;
   0,
   872415232,
   3212836864,
   1065353216,
   0,
   0,
   3035338687,
   872415232,
   3212836864,
   1065353216,
   694917055,
   3035338687,
   3039867342,
   872415232,
   3212836864,
   1065353216,
   699445710,
   3039867342,
   0,
   872415232,
   3212836864,
   1065353216,
   0,
   0,
   887855060,
   872415232,
   3212836864,
   1065353216,
   2842400724,
   887855060,
   879466458,
   872415232,
   3212836864,
   1065353216,
   2834012122,
   879466458,
   3039867342,
   872415232,
   3212836864,
   1065353216,
   699445710,
   3039867342,
   887855060,
   872415232,
   3212836864,
   1065353216,
   2842400724,
   887855060,
   3026950055,
   872415232,
   3212836864,
   1065353216,
   686528423,
   3026950055,
   0,
   872415232,
   3212836864,
   1065353216,
   0,
   0,
   0,
   872415232,
   3212836864,
   1065353216,
   0,
   0,
   0,
   872415232,
   3212836864,
   1065353216,
   0,
   0,
   887855051,
   872415232,
   3212836864,
   1065353216,
   2842400715,
   887855051,
   0,
   872415232,
   3212836864,
   1065353216,
   0,
   0,
   892383702,
   872415232,
   3212836864,
   1065353216,
   2846929366,
   892383702,
   0,
   872415232,
   3212836864,
   1065353216,
   0,
   0,
   0,
   872415232,
   3212836864,
   1065353216,
   0,
   0,
   879466452,
   872415232,
   3212836864,
   1065353216,
   2834012116,
   879466452,
   0,
   872415232,
   3212836864,
   1065353216,
   0,
   0,
   3035338687,
   872415232,
   3212836864,
   1065353216,
   694917055,
   3035338687,
   3039867342,
   872415232,
   3212836864,
   1065353216,
   699445710,
   3039867342,
   887855060,
   872415232,
   3212836864,
   1065353216,
   2842400724,
   887855060,
   0,
   872415232,
   3212836864,
   1065353216,
   0,
   0,
   896243668,
   872415232,
   3212836864,
   1065353216,
   2850789332,
   896243668,
   724216491,
   872415232,
   3212836864,
   1065353216,
   2678762155,
   724216491;
  }

  MeshMaterialList mtls {
   1;
   32;
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
   0,
   0,
   0,
   0;

   Material Dflt_Material {
    0.800000;0.800000;0.800000;1.000000;;
    16.000000;
    1.000000;1.000000;1.000000;;
    0.000000;0.000000;0.000000;;

    EffectInstance Effect {
     "Xoliulshader_1.3.fx";

     EffectParamDWord {
      "light1_Position";
      0;
     }

     EffectParamDWord {
      "__PlaceHolder_255_shadowTerm1";
      0;
     }

     EffectParamDWord {
      "bUseShadow1";
      0;
     }

     EffectParamFloats {
      "Shadow1Soft";
      1;
      0.000000;
     }

     EffectParamFloats {
      "Shadow1Strength";
      1;
      1.000000;
     }

     EffectParamFloats {
      "DistanceBlur";
      1;
      3.000000;
     }

     EffectParamDWord {
      "light2_Position";
      0;
     }

     EffectParamDWord {
      "light3_Position";
      0;
     }

     EffectParamDWord {
      "bUseHalfLambert";
      0;
     }

     EffectParamFloats {
      "HalfLambertPower";
      1;
      2.000000;
     }

     EffectParamFloats {
      "ambientcolor";
      4;
      0.000000,
      0.000000,
      0.000000,
      0.000000;
     }

     EffectParamDWord {
      "bUseIBL";
      0;
     }

     EffectParamDWord {
      "bUseIBLCubeMap";
      0;
     }

     EffectParamFloats {
      "IBLBlur";
      1;
      6.000000;
     }

     EffectParamFloats {
      "IBLmultiplier";
      1;
      0.500000;
     }

     EffectParamDWord {
      "numberOfActiveLights";
      1;
     }

     EffectParamDWord {
      "bUseDiffuseMap";
      1;
     }

     EffectParamFloats {
      "diffuseColor";
      4;
      0.500000,
      0.500000,
      0.500000,
      1.000000;
     }

     EffectParamString {
      "diffuseMap";
      "Pilar_Base_Color.tga";
     }

     EffectParamDWord {
      "bColorDiffuse";
      0;
     }

     EffectParamDWord {
      "bUseAlpha";
      0;
     }

     EffectParamFloats {
      "GlobalOpacity";
      1;
      1.000000;
     }

     EffectParamDWord {
      "bUseSpecMap";
      1;
     }

     EffectParamFloats {
      "specularColor";
      4;
      1.000000,
      1.000000,
      1.000000,
      1.000000;
     }

     EffectParamFloats {
      "speclevel";
      1;
      1.000000;
     }

     EffectParamString {
      "specularMap";
      "Pilar_Specular.tga";
     }

     EffectParamDWord {
      "bUseGlossMap";
      1;
     }

     EffectParamString {
      "glossMap";
      "Pilar_Glossiness.tga";
     }

     EffectParamFloats {
      "glossiness";
      1;
      25.000000;
     }

     EffectParamFloats {
      "glossoffset";
      1;
      10.000000;
     }

     EffectParamDWord {
      "bUseNormalMap";
      1;
     }

     EffectParamDWord {
      "bUseObjectNormals";
      0;
     }

     EffectParamString {
      "normalMap";
      "Pilar_Normal.tga";
     }

     EffectParamDWord {
      "bFlipGreenChannel";
      0;
     }

     EffectParamDWord {
      "bUseSIMap";
      0;
     }

     EffectParamFloats {
      "siMapMult";
      1;
      1.000000;
     }

     EffectParamFloats {
      "siLevel";
      1;
      0.000000;
     }

     EffectParamDWord {
      "bUseFresnel";
      0;
     }

     EffectParamDWord {
      "bAlphaMasksFresnel";
      0;
     }

     EffectParamFloats {
      "FresnelPower";
      1;
      3.000000;
     }

     EffectParamFloats {
      "FresnelBias";
      1;
      0.000000;
     }

     EffectParamFloats {
      "FresnelMult";
      1;
      2.000000;
     }

     EffectParamFloats {
      "FresnelColor";
      4;
      1.000000,
      1.000000,
      1.000000,
      0.000000;
     }

     EffectParamFloats {
      "FresnelMaskHardness";
      1;
      4.000000;
     }

     EffectParamDWord {
      "bUseWorldMask";
      1;
     }

     EffectParamDWord {
      "bUseReflMap";
      0;
     }

     EffectParamDWord {
      "bUseCubeMap";
      0;
     }

     EffectParamFloats {
      "CubeMapBlur";
      1;
      0.000000;
     }

     EffectParamDWord {
      "bUseReflGloss";
      0;
     }
    }

    TextureFilename Diffuse {
     "Pilar_Base_Color.tga";
    }
   }
  }
 }
}