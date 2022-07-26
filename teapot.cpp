
#include "model.h"
#include "lighting.h"

namespace {

Vec3D teapot_vertices[] = {
  { 1.385776f, 2.429268f, 0.111367f },
  { 1.154212f, 2.422741f, 0.840016f },
  { -0.203208f, 2.432654f, 1.380593f },
  { -0.789935f, 2.419499f, 1.167008f },
  { -1.404081f, 2.445989f, -0.049658f },
  { -1.167008f, 2.419499f, -0.789935f },
  { -0.163244f, 2.506464f, -1.426775f },
  { 0.318594f, 2.519800f, -1.394937f },
  { 0.559900f, 2.503822f, -1.325516f },
  { 1.267550f, 2.453249f, -0.612298f },
  { 1.294526f, 2.469529f, 0.728155f },
  { 1.040163f, 2.493945f, -1.035751f },
  { 1.340135f, 2.512751f, -0.540660f },
  { -0.682962f, 2.468137f, -1.215207f },
  { 1.465330f, 2.479053f, 0.075311f },
  { 1.378168f, 2.490340f, 0.471924f },
  { 1.475202f, 2.371656f, -0.399666f },
  { 0.932202f, 2.501646f, 1.121886f },
  { 0.653865f, 2.402498f, 1.367196f },
  { 0.199840f, 2.491941f, 1.436064f },
  { -0.161822f, 2.485616f, 1.451249f },
  { -0.483241f, 2.496330f, 1.370113f },
  { -1.065598f, 2.476223f, 1.025902f },
  { -1.345182f, 2.506005f, 0.527405f },
  { -1.452624f, 2.458915f, 0.237812f },
  { -1.407734f, 2.497258f, -0.379550f },
  { -1.165854f, 2.485900f, -0.882028f },
  { -0.757315f, 2.461818f, -1.290351f },
  { 0.115836f, 1.818738f, -1.773163f },
  { -1.629290f, 2.124355f, -0.167837f },
  { 1.459896f, 1.963142f, -0.902583f },
  { 1.660287f, 1.967528f, 0.412932f },
  { 1.527531f, 1.532506f, 1.125896f },
  { 1.116134f, 1.962198f, 1.305583f },
  { 0.407565f, 1.966504f, 1.662031f },
  { -0.000312f, 1.924225f, 1.722484f },
  { -0.412932f, 1.967525f, 1.660289f },
  { -0.901443f, 1.975418f, 1.454201f },
  { -1.305583f, 1.962199f, 1.116134f },
  { -1.579779f, 1.964619f, 0.665240f },
  { -1.565249f, 1.990402f, -0.671110f },
  { -1.116134f, 1.962198f, -1.305583f },
  { -0.704921f, 1.736549f, -1.673385f },
  { -0.295176f, 1.727247f, -1.786489f },
  { 0.578925f, 1.728242f, -1.717660f },
  { 0.837708f, 1.748938f, -1.601067f },
  { 1.892607f, 1.502058f, -0.180938f },
  { -0.159038f, 1.366372f, 1.932857f },
  { -0.617091f, 1.362101f, 1.837071f },
  { -0.895484f, 1.362008f, 1.721194f },
  { -1.267974f, 1.365327f, 1.477336f },
  { -1.653955f, 1.365256f, 1.025214f },
  { -1.885393f, 1.365284f, 0.464769f },
  { -1.808669f, 1.725901f, 0.149409f },
  { -1.463052f, 1.728063f, -1.076010f },
  { 1.182120f, 1.637652f, -1.433336f },
  { -1.697917f, 1.246977f, -1.015194f },
  { -1.391897f, 1.275564f, -1.392287f },
  { -1.070897f, 1.245975f, -1.664011f },
  { -0.476501f, 1.163719f, -1.929163f },
  { 0.198128f, 1.247449f, -1.962245f },
  { 0.630801f, 1.161894f, -1.879532f },
  { 0.915585f, 1.161681f, -1.761099f },
  { 1.653955f, 1.365256f, -1.025214f },
  { 1.837257f, 1.361263f, -0.617293f },
  { 1.909275f, 1.362296f, 0.317373f },
  { 1.790078f, 1.365874f, 0.758039f },
  { 1.266773f, 1.365246f, 1.478392f },
  { 0.895630f, 1.361483f, 1.721286f },
  { 0.617292f, 1.361263f, 1.837257f },
  { 0.317540f, 1.361123f, 1.909585f },
  { -1.911103f, 1.278032f, -0.472727f },
  { 1.328940f, 1.039709f, -1.513206f },
  { 1.621168f, 0.870395f, -1.193076f },
  { 1.847801f, 0.889399f, -0.806694f },
  { 1.959463f, 0.749001f, -0.428122f },
  { 2.003443f, 1.030874f, 0.117403f },
  { 1.854574f, 0.944835f, 0.782043f },
  { 1.531447f, 0.944704f, 1.310429f },
  { 1.052483f, 0.884639f, 1.721495f },
  { 0.484183f, 0.944488f, 1.951221f },
  { -0.782043f, 0.944835f, 1.854574f },
  { -1.430840f, 0.945658f, 1.433813f },
  { -1.984985f, 0.726601f, -0.165142f },
  { -1.851702f, 0.826211f, -0.779170f },
  { -1.529559f, 0.826113f, -1.306837f },
  { -1.063278f, 0.826022f, -1.706730f },
  { -0.639951f, 0.727860f, -1.886045f },
  { -0.167399f, 0.825771f, -1.997373f },
  { 0.779170f, 0.826211f, -1.851702f },
  { 1.935555f, 0.589378f, 0.102900f },
  { 1.916224f, 0.676282f, 0.467456f },
  { 1.681248f, 0.733225f, 1.067070f },
  { 1.297938f, 0.720933f, 1.507480f },
  { 0.478408f, 0.675647f, 1.913369f },
  { 0.005960f, 0.768260f, 2.004151f },
  { -0.323129f, 0.768646f, 1.979308f },
  { -0.764150f, 0.676195f, 1.820868f },
  { -1.164343f, 0.676983f, 1.591105f },
  { -1.497551f, 0.676045f, 1.291455f },
  { -1.843432f, 0.787500f, 0.817946f },
  { -1.977332f, 0.767870f, 0.334759f },
  { -1.636911f, 0.530688f, -0.960638f },
  { -1.477714f, 0.612106f, -1.260983f },
  { -1.146274f, 0.614248f, -1.562191f },
  { -0.782477f, 0.529815f, -1.727270f },
  { -0.069846f, 0.522760f, -1.891994f },
  { 0.426349f, 0.711604f, -1.943492f },
  { 1.283109f, 0.676102f, -1.504709f },
  { 1.647373f, 0.612000f, -1.027685f },
  { 0.777735f, 0.493384f, 1.705288f },
  { -1.798880f, 0.544699f, 0.611223f },
  { 1.740560f, 0.535308f, 0.759598f },
  { 1.531115f, 0.436906f, 0.986288f },
  { 1.199790f, 0.458440f, 1.396513f },
  { -1.427653f, 0.397514f, 1.077994f },
  { -1.795720f, 0.430203f, 0.153383f },
  { -1.850568f, 0.544208f, -0.448529f },
  { 0.343640f, 0.243865f, -1.578247f },
  { 0.960638f, 0.530688f, -1.636911f },
  { 1.428038f, 0.384217f, -1.057826f },
  { 0.028176f, 0.308128f, 1.696389f },
  { -0.809388f, 0.394584f, 1.590422f },
  { -1.167083f, 0.401121f, -1.348924f },
  { 1.727700f, 0.409267f, -0.454439f },
  { -0.708924f, 0.100824f, 1.309853f },
  { -1.303033f, 0.117067f, 0.679304f },
  { -1.409387f, 0.077952f, 0.130677f },
  { -1.452617f, 0.175153f, -0.468159f },
  { -0.489353f, 0.175154f, -1.445781f },
  { 0.856042f, 0.184775f, -1.274520f },
  { 1.074634f, 0.108425f, -1.006431f },
  { 1.385156f, 0.082231f, -0.426772f },
  { 1.522905f, 0.174800f, -0.011590f },
  { 1.425968f, 0.098644f, 0.302969f },
  { -0.021785f, 0.048739f, 1.394628f },
  { -1.120889f, 0.177950f, -1.043906f },
  { -0.167488f, 0.000778f, -0.606076f },
  { -1.110600f, 0.023832f, -0.264167f },
  { -1.366325f, 0.078983f, -0.620963f },
  { -0.654283f, 0.058893f, -1.290950f },
  { 0.245485f, 0.051792f, -1.388857f },
  { 0.744478f, 0.043811f, -1.140790f },
  { 1.299725f, 0.041130f, -0.057300f },
  { 1.151075f, 0.071228f, 0.849199f },
  { 0.742947f, 0.007321f, 0.423864f },
  { 0.749562f, 0.076768f, 1.227621f },
  { -0.763054f, 0.025908f, 0.986237f },
  { -0.459225f, 3.105135f, 0.027160f },
  { 0.134322f, 3.094899f, -0.392308f },
  { 0.317820f, 3.110112f, 0.355944f },
  { 0.128527f, 2.727887f, -0.061607f },
  { -0.123646f, 2.699805f, 0.019999f },
  { -0.351683f, 2.631644f, 0.075230f },
  { 0.019939f, 2.641318f, -0.324849f },
  { 0.009477f, 2.630215f, 0.370694f },
  { -0.458157f, 2.511402f, -1.019442f },
  { 1.142298f, 2.478913f, -0.513085f },
  { 0.761125f, 2.561359f, 0.176878f },
  { 0.093534f, 2.481767f, 1.227861f },
  { -1.176011f, 2.476750f, 0.440808f },
  { 1.290568f, 2.454636f, 0.021699f },
  { -0.774207f, 2.444813f, -1.054708f },
  { -0.014706f, 2.458712f, -1.268196f },
  { 0.580148f, 2.475602f, -1.132039f },
  { 0.852128f, 2.469975f, 0.971616f },
  { -0.658910f, 2.470007f, 1.111154f },
  { -1.234731f, 2.483540f, -0.238034f },
  { -1.606265f, 2.010464f, -0.029607f },
  { -1.565132f, 2.105494f, 0.222062f },
  { -1.513619f, 2.219341f, 0.183846f },
  { -2.480936f, 0.943795f, 0.179799f },
  { -2.714579f, 2.219581f, 0.093524f },
  { -3.008564f, 1.737021f, 0.091558f },
  { -1.895394f, 0.579661f, -0.005795f },
  { -2.789688f, 1.414423f, 0.229602f },
  { -2.804990f, 2.030170f, 0.231670f },
  { -2.009006f, 0.777749f, 0.251205f },
  { -2.394357f, 1.134388f, 0.127447f },
  { -2.440370f, 2.003124f, 0.045830f },
  { -2.716414f, 1.758385f, 0.106128f },
  { -2.743940f, 1.738775f, -0.158282f },
  { -2.014333f, 0.951470f, 0.007958f },
  { -2.086370f, 0.694113f, -0.174872f },
  { -2.816984f, 1.227589f, -0.031507f },
  { -2.875686f, 2.122751f, -0.173920f },
  { -2.425160f, 1.132488f, -0.204475f },
  { -2.232368f, 2.118769f, -0.256873f },
  { -2.907805f, 1.553382f, -0.214976f },
  { -1.510033f, 2.224911f, -0.190454f },
  { 1.706529f, 1.430439f, -0.015561f },
  { 2.109929f, 1.318528f, 0.413675f },
  { 1.700376f, 1.348218f, 0.330643f },
  { 1.725449f, 0.967481f, 0.511458f },
  { 1.700458f, 0.744095f, 0.405058f },
  { 1.699902f, 0.599347f, 0.075027f },
  { 2.063889f, 0.697626f, 0.096718f },
  { 2.318867f, 0.838374f, -0.079245f },
  { 2.515840f, 1.071088f, 0.212796f },
  { 2.858654f, 1.986855f, -0.047408f },
  { 2.237783f, 0.877430f, 0.360182f },
  { 2.778312f, 1.858341f, 0.165629f },
  { 2.990550f, 2.281491f, 0.166093f },
  { 2.483664f, 1.351639f, 0.398044f },
  { 2.824583f, 2.396869f, 0.165893f },
  { 2.206156f, 1.504883f, 0.219243f },
  { 2.379820f, 1.522281f, 0.355736f },
  { 1.720992f, 1.362472f, -0.270804f },
  { 2.085533f, 1.474231f, -0.080585f },
  { 2.321258f, 1.662272f, -0.148410f },
  { 2.543268f, 2.220125f, -0.071957f },
  { 2.629401f, 2.414427f, 0.016844f },
  { 2.654333f, 1.318285f, -0.098214f },
  { 2.054683f, 0.730528f, -0.237597f },
  { 1.699801f, 0.645677f, -0.256118f },
  { 2.203614f, 0.911462f, -0.398318f },
  { 2.501847f, 1.129063f, -0.323346f },
  { 3.107668f, 2.308905f, -0.121525f },
  { 1.707056f, 0.897130f, -0.491766f },
  { 2.852654f, 2.297523f, -0.182337f },
  { 2.306483f, 1.268183f, -0.447528f },
  { 2.194281f, 1.397477f, -0.349459f },
  { 1.700352f, 1.156009f, -0.481739f },
};

Triangle teapot_tris[] = {
  { { 9, 0, 12 }, 0 },
  { { 2, 3, 21 }, 0 },
  { { 4, 5, 25 }, 0 },
  { { 12, 0, 14 }, 0 },
  { { 0, 15, 14 }, 0 },
  { { 0, 1, 15 }, 0 },
  { { 1, 10, 15 }, 0 },
  { { 1, 17, 10 }, 0 },
  { { 1, 19, 17 }, 0 },
  { { 2, 21, 20 }, 0 },
  { { 21, 3, 22 }, 0 },
  { { 3, 23, 22 }, 0 },
  { { 25, 5, 26 }, 0 },
  { { 5, 13, 26 }, 0 },
  { { 8, 9, 11 }, 0 },
  { { 9, 12, 11 }, 0 },
  { { 12, 14, 16 }, 0 },
  { { 17, 19, 18 }, 0 },
  { { 23, 4, 24 }, 0 },
  { { 4, 25, 24 }, 0 },
  { { 26, 13, 27 }, 0 },
  { { 13, 6, 27 }, 0 },
  { { 24, 25, 29 }, 0 },
  { { 6, 7, 28 }, 0 },
  { { 8, 11, 45 }, 0 },
  { { 21, 22, 37 }, 0 },
  { { 25, 26, 40 }, 0 },
  { { 7, 8, 44 }, 0 },
  { { 7, 44, 28 }, 0 },
  { { 8, 45, 44 }, 0 },
  { { 45, 11, 55 }, 0 },
  { { 11, 12, 30 }, 0 },
  { { 12, 16, 30 }, 0 },
  { { 14, 15, 31 }, 0 },
  { { 15, 10, 31 }, 0 },
  { { 10, 17, 33 }, 0 },
  { { 10, 33, 32 }, 0 },
  { { 17, 18, 33 }, 0 },
  { { 18, 19, 34 }, 0 },
  { { 19, 20, 35 }, 0 },
  { { 19, 35, 34 }, 0 },
  { { 20, 36, 35 }, 0 },
  { { 20, 21, 36 }, 0 },
  { { 21, 37, 36 }, 0 },
  { { 22, 38, 37 }, 0 },
  { { 22, 23, 39 }, 0 },
  { { 22, 39, 38 }, 0 },
  { { 23, 24, 53 }, 0 },
  { { 23, 53, 39 }, 0 },
  { { 24, 29, 53 }, 0 },
  { { 25, 40, 29 }, 0 },
  { { 40, 26, 54 }, 0 },
  { { 26, 27, 41 }, 0 },
  { { 26, 41, 54 }, 0 },
  { { 27, 42, 41 }, 0 },
  { { 27, 6, 43 }, 0 },
  { { 27, 43, 42 }, 0 },
  { { 6, 28, 43 }, 0 },
  { { 11, 30, 55 }, 0 },
  { { 16, 14, 46 }, 0 },
  { { 14, 31, 46 }, 0 },
  { { 41, 42, 58 }, 0 },
  { { 28, 44, 60 }, 0 },
  { { 55, 30, 63 }, 0 },
  { { 30, 16, 64 }, 0 },
  { { 30, 64, 63 }, 0 },
  { { 16, 46, 64 }, 0 },
  { { 46, 31, 65 }, 0 },
  { { 31, 66, 65 }, 0 },
  { { 31, 10, 66 }, 0 },
  { { 10, 32, 66 }, 0 },
  { { 32, 33, 67 }, 0 },
  { { 33, 18, 68 }, 0 },
  { { 33, 68, 67 }, 0 },
  { { 18, 34, 69 }, 0 },
  { { 18, 69, 68 }, 0 },
  { { 34, 70, 69 }, 0 },
  { { 34, 35, 47 }, 0 },
  { { 34, 47, 70 }, 0 },
  { { 35, 36, 47 }, 0 },
  { { 36, 48, 47 }, 0 },
  { { 36, 37, 49 }, 0 },
  { { 36, 49, 48 }, 0 },
  { { 37, 50, 49 }, 0 },
  { { 37, 38, 50 }, 0 },
  { { 38, 51, 50 }, 0 },
  { { 38, 39, 51 }, 0 },
  { { 39, 52, 51 }, 0 },
  { { 39, 53, 52 }, 0 },
  { { 53, 29, 71 }, 0 },
  { { 29, 40, 71 }, 0 },
  { { 40, 56, 71 }, 0 },
  { { 40, 54, 56 }, 0 },
  { { 54, 41, 57 }, 0 },
  { { 41, 58, 57 }, 0 },
  { { 54, 57, 56 }, 0 },
  { { 42, 59, 58 }, 0 },
  { { 42, 43, 59 }, 0 },
  { { 43, 28, 60 }, 0 },
  { { 43, 60, 59 }, 0 },
  { { 60, 44, 61 }, 0 },
  { { 44, 45, 62 }, 0 },
  { { 44, 62, 61 }, 0 },
  { { 45, 55, 62 }, 0 },
  { { 55, 63, 72 }, 0 },
  { { 46, 65, 76 }, 0 },
  { { 52, 53, 182 }, 0 },
  { { 53, 71, 182 }, 0 },
  { { 62, 55, 72 }, 0 },
  { { 72, 63, 73 }, 0 },
  { { 63, 74, 73 }, 0 },
  { { 63, 64, 74 }, 0 },
  { { 64, 46, 75 }, 0 },
  { { 64, 75, 74 }, 0 },
  { { 46, 76, 75 }, 0 },
  { { 65, 66, 77 }, 0 },
  { { 65, 77, 76 }, 0 },
  { { 66, 32, 78 }, 0 },
  { { 66, 78, 77 }, 0 },
  { { 32, 67, 78 }, 0 },
  { { 67, 79, 78 }, 0 },
  { { 67, 68, 79 }, 0 },
  { { 68, 69, 80 }, 0 },
  { { 68, 80, 79 }, 0 },
  { { 69, 70, 80 }, 0 },
  { { 70, 47, 95 }, 0 },
  { { 70, 95, 80 }, 0 },
  { { 47, 96, 95 }, 0 },
  { { 47, 48, 81 }, 0 },
  { { 47, 81, 96 }, 0 },
  { { 48, 49, 81 }, 0 },
  { { 49, 50, 82 }, 0 },
  { { 49, 82, 81 }, 0 },
  { { 50, 51, 82 }, 0 },
  { { 51, 100, 82 }, 0 },
  { { 51, 52, 100 }, 0 },
  { { 52, 101, 100 }, 0 },
  { { 52, 182, 101 }, 0 },
  { { 71, 84, 83 }, 0 },
  { { 71, 56, 84 }, 0 },
  { { 56, 85, 84 }, 0 },
  { { 56, 57, 85 }, 0 },
  { { 57, 58, 86 }, 0 },
  { { 57, 86, 85 }, 0 },
  { { 58, 59, 87 }, 0 },
  { { 58, 87, 86 }, 0 },
  { { 59, 88, 87 }, 0 },
  { { 59, 60, 88 }, 0 },
  { { 60, 107, 88 }, 0 },
  { { 60, 61, 89 }, 0 },
  { { 60, 89, 107 }, 0 },
  { { 61, 62, 89 }, 0 },
  { { 62, 72, 89 }, 0 },
  { { 182, 71, 83 }, 0 },
  { { 89, 72, 108 }, 0 },
  { { 72, 73, 108 }, 0 },
  { { 75, 76, 90 }, 0 },
  { { 76, 91, 90 }, 0 },
  { { 76, 77, 91 }, 0 },
  { { 77, 92, 91 }, 0 },
  { { 77, 78, 92 }, 0 },
  { { 78, 93, 92 }, 0 },
  { { 78, 79, 93 }, 0 },
  { { 79, 80, 94 }, 0 },
  { { 80, 95, 94 }, 0 },
  { { 96, 81, 97 }, 0 },
  { { 81, 82, 98 }, 0 },
  { { 81, 98, 97 }, 0 },
  { { 82, 99, 98 }, 0 },
  { { 82, 100, 99 }, 0 },
  { { 101, 182, 83 }, 0 },
  { { 83, 84, 117 }, 0 },
  { { 84, 102, 117 }, 0 },
  { { 84, 85, 103 }, 0 },
  { { 84, 103, 102 }, 0 },
  { { 85, 86, 104 }, 0 },
  { { 85, 104, 103 }, 0 },
  { { 86, 105, 104 }, 0 },
  { { 86, 87, 105 }, 0 },
  { { 87, 88, 106 }, 0 },
  { { 88, 107, 106 }, 0 },
  { { 89, 119, 107 }, 0 },
  { { 89, 108, 119 }, 0 },
  { { 108, 73, 109 }, 0 },
  { { 73, 74, 109 }, 0 },
  { { 74, 75, 109 }, 0 },
  { { 91, 92, 112 }, 0 },
  { { 93, 79, 110 }, 0 },
  { { 79, 94, 110 }, 0 },
  { { 100, 101, 111 }, 0 },
  { { 112, 92, 113 }, 0 },
  { { 92, 93, 114 }, 0 },
  { { 92, 114, 113 }, 0 },
  { { 93, 110, 114 }, 0 },
  { { 100, 111, 115 }, 0 },
  { { 111, 101, 116 }, 0 },
  { { 101, 83, 116 }, 0 },
  { { 83, 117, 116 }, 0 },
  { { 103, 123, 102 }, 0 },
  { { 103, 104, 123 }, 0 },
  { { 104, 105, 123 }, 0 },
  { { 87, 106, 105 }, 0 },
  { { 107, 118, 106 }, 0 },
  { { 107, 119, 118 }, 0 },
  { { 108, 120, 119 }, 0 },
  { { 108, 109, 120 }, 0 },
  { { 109, 75, 124 }, 0 },
  { { 109, 124, 120 }, 0 },
  { { 75, 90, 124 }, 0 },
  { { 91, 112, 90 }, 0 },
  { { 94, 121, 110 }, 0 },
  { { 94, 95, 121 }, 0 },
  { { 95, 96, 121 }, 0 },
  { { 96, 97, 122 }, 0 },
  { { 96, 122, 121 }, 0 },
  { { 97, 98, 122 }, 0 },
  { { 98, 99, 115 }, 0 },
  { { 98, 115, 122 }, 0 },
  { { 99, 100, 115 }, 0 },
  { { 115, 111, 126 }, 0 },
  { { 111, 116, 127 }, 0 },
  { { 111, 127, 126 }, 0 },
  { { 116, 117, 128 }, 0 },
  { { 116, 128, 127 }, 0 },
  { { 117, 102, 128 }, 0 },
  { { 102, 136, 128 }, 0 },
  { { 102, 123, 136 }, 0 },
  { { 123, 105, 129 }, 0 },
  { { 105, 106, 129 }, 0 },
  { { 106, 118, 129 }, 0 },
  { { 118, 119, 130 }, 0 },
  { { 119, 120, 130 }, 0 },
  { { 124, 90, 133 }, 0 },
  { { 90, 112, 134 }, 0 },
  { { 90, 134, 133 }, 0 },
  { { 112, 113, 134 }, 0 },
  { { 121, 122, 135 }, 0 },
  { { 113, 114, 144 }, 0 },
  { { 122, 115, 125 }, 0 },
  { { 115, 126, 125 }, 0 },
  { { 123, 129, 136 }, 0 },
  { { 120, 131, 130 }, 0 },
  { { 131, 120, 132 }, 0 },
  { { 120, 124, 132 }, 0 },
  { { 124, 133, 132 }, 0 },
  { { 134, 113, 144 }, 0 },
  { { 144, 114, 146 }, 0 },
  { { 114, 110, 146 }, 0 },
  { { 110, 121, 146 }, 0 },
  { { 122, 125, 135 }, 0 },
  { { 147, 135, 125 }, 0 },
  { { 137, 145, 147 }, 0 },
  { { 147, 125, 126 }, 0 },
  { { 137, 147, 138 }, 0 },
  { { 127, 147, 126 }, 0 },
  { { 138, 147, 127 }, 0 },
  { { 138, 127, 139 }, 0 },
  { { 139, 127, 128 }, 0 },
  { { 137, 138, 140 }, 0 },
  { { 140, 138, 139 }, 0 },
  { { 139, 128, 136 }, 0 },
  { { 140, 139, 136 }, 0 },
  { { 140, 136, 129 }, 0 },
  { { 137, 140, 141 }, 0 },
  { { 141, 140, 129 }, 0 },
  { { 141, 129, 118 }, 0 },
  { { 142, 141, 118 }, 0 },
  { { 142, 118, 130 }, 0 },
  { { 137, 141, 142 }, 0 },
  { { 131, 142, 130 }, 0 },
  { { 132, 142, 131 }, 0 },
  { { 143, 142, 132 }, 0 },
  { { 145, 137, 142 }, 0 },
  { { 145, 142, 143 }, 0 },
  { { 143, 132, 134 }, 0 },
  { { 134, 132, 133 }, 0 },
  { { 144, 143, 134 }, 0 },
  { { 145, 143, 144 }, 0 },
  { { 145, 144, 146 }, 0 },
  { { 135, 145, 146 }, 0 },
  { { 147, 145, 135 }, 0 },
  { { 135, 146, 121 }, 0 },
  { { 150, 149, 148 }, 0 },
  { { 149, 150, 151 }, 0 },
  { { 148, 149, 152 }, 0 },
  { { 150, 152, 151 }, 0 },
  { { 150, 148, 152 }, 0 },
  { { 149, 151, 152 }, 0 },
  { { 152, 155, 151 }, 0 },
  { { 152, 153, 155 }, 0 },
  { { 152, 154, 153 }, 0 },
  { { 152, 151, 154 }, 0 },
  { { 151, 158, 154 }, 0 },
  { { 151, 155, 158 }, 0 },
  { { 153, 154, 167 }, 0 },
  { { 154, 164, 156 }, 0 },
  { { 154, 157, 164 }, 0 },
  { { 154, 158, 157 }, 0 },
  { { 158, 155, 165 }, 0 },
  { { 155, 159, 165 }, 0 },
  { { 155, 166, 159 }, 0 },
  { { 155, 153, 166 }, 0 },
  { { 153, 160, 166 }, 0 },
  { { 153, 167, 160 }, 0 },
  { { 167, 154, 156 }, 0 },
  { { 156, 164, 163 }, 0 },
  { { 157, 158, 161 }, 0 },
  { { 167, 156, 162 }, 0 },
  { { 158, 165, 161 }, 0 },
  { { 156, 163, 162 }, 0 },
  { { 168, 169, 179 }, 0 },
  { { 170, 189, 172 }, 0 },
  { { 184, 173, 188 }, 0 },
  { { 183, 171, 184 }, 0 },
  { { 171, 183, 174 }, 0 },
  { { 172, 185, 173 }, 0 },
  { { 177, 171, 174 }, 0 },
  { { 175, 184, 171 }, 0 },
  { { 175, 173, 184 }, 0 },
  { { 176, 172, 173 }, 0 },
  { { 170, 172, 176 }, 0 },
  { { 176, 173, 175 }, 0 },
  { { 175, 171, 177 }, 0 },
  { { 169, 170, 176 }, 0 },
  { { 178, 175, 177 }, 0 },
  { { 180, 175, 178 }, 0 },
  { { 180, 176, 175 }, 0 },
  { { 169, 176, 179 }, 0 },
  { { 179, 176, 180 }, 0 },
  { { 178, 177, 182 }, 0 },
  { { 181, 180, 178 }, 0 },
  { { 181, 178, 186 }, 0 },
  { { 182, 183, 186 }, 0 },
  { { 188, 173, 185 }, 0 },
  { { 187, 185, 172 }, 0 },
  { { 187, 172, 189 }, 0 },
  { { 186, 183, 184 }, 0 },
  { { 186, 184, 188 }, 0 },
  { { 188, 185, 181 }, 0 },
  { { 187, 189, 168 }, 0 },
  { { 179, 185, 187 }, 0 },
  { { 181, 185, 179 }, 0 },
  { { 181, 186, 188 }, 0 },
  { { 181, 179, 180 }, 0 },
  { { 179, 187, 168 }, 0 },
  { { 178, 182, 186 }, 0 },
  { { 192, 191, 190 }, 0 },
  { { 192, 193, 191 }, 0 },
  { { 194, 200, 193 }, 0 },
  { { 194, 196, 200 }, 0 },
  { { 194, 195, 196 }, 0 },
  { { 213, 196, 195 }, 0 },
  { { 213, 195, 214 }, 0 },
  { { 197, 196, 213 }, 0 },
  { { 216, 198, 197 }, 0 },
  { { 212, 198, 216 }, 0 },
  { { 219, 202, 217 }, 0 },
  { { 199, 217, 202 }, 0 },
  { { 212, 199, 201 }, 0 },
  { { 200, 197, 198 }, 0 },
  { { 196, 197, 200 }, 0 },
  { { 198, 212, 201 }, 0 },
  { { 201, 199, 202 }, 0 },
  { { 203, 198, 201 }, 0 },
  { { 200, 198, 203 }, 0 },
  { { 203, 201, 204 }, 0 },
  { { 204, 201, 202 }, 0 },
  { { 193, 200, 203 }, 0 },
  { { 191, 193, 203 }, 0 },
  { { 191, 203, 206 }, 0 },
  { { 206, 203, 204 }, 0 },
  { { 206, 204, 211 }, 0 },
  { { 205, 191, 206 }, 0 },
  { { 210, 206, 211 }, 0 },
  { { 209, 206, 210 }, 0 },
  { { 209, 205, 206 }, 0 },
  { { 190, 191, 205 }, 0 },
  { { 208, 190, 205 }, 0 },
  { { 208, 207, 190 }, 0 },
  { { 219, 199, 212 }, 0 },
  { { 216, 197, 215 }, 0 },
  { { 215, 197, 213 }, 0 },
  { { 215, 213, 214 }, 0 },
  { { 219, 212, 216 }, 0 },
  { { 217, 199, 219 }, 0 },
  { { 215, 214, 218 }, 0 },
  { { 220, 215, 218 }, 0 },
  { { 220, 216, 215 }, 0 },
  { { 219, 216, 220 }, 0 },
  { { 220, 218, 222 }, 0 },
  { { 221, 220, 222 }, 0 },
  { { 209, 220, 221 }, 0 },
  { { 209, 219, 220 }, 0 },
  { { 210, 219, 209 }, 0 },
  { { 211, 219, 210 }, 0 },
  { { 221, 222, 207 }, 0 },
  { { 208, 221, 207 }, 0 },
  { { 209, 221, 208 }, 0 },
  { { 208, 205, 209 }, 0 },
};

Material teapot_mats[1];

Model teapot_model {
  teapot_vertices,
  teapot_tris,
  teapot_mats,
  sizeof(teapot_vertices) / sizeof(teapot_vertices[0]),
  sizeof(teapot_mats) / sizeof(teapot_mats[0]),
  sizeof(teapot_tris) / sizeof(teapot_tris[0])
};

bool teapot_model_inited = false;
}

Model& get_teapot_model() {
  if (!teapot_model_inited) {
    teapot_mats[0] = make_material_for_colour(pimoroni::RGB(200, 200, 255));
    
    for (uint8_t i = 0; i < teapot_model.num_vertices; ++i)
    {
        teapot_vertices[i].y -= fixed_t(2);
        teapot_vertices[i].z += fixed_t(6);
    }

    set_triangle_normals(teapot_model);
    teapot_model_inited = true;
  }
  
  return teapot_model;
}
