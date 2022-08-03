// Teapot is the standard Utah teapot reduced to 400 faces in MeshLab

#include "common.h"
#include "model.h"
#include "lighting.h"

namespace {

Vec3D teapot_vertices[] = {
  { 1.385776f, 2.429268f, 0.111367f },
  { 1.065998f, 2.407617f, 0.913919f },
  { 0.826899f, 2.429277f, 1.118568f },
  { 0.285458f, 2.455801f, 1.353677f },
  { -0.203208f, 2.432654f, 1.380593f },
  { -0.789935f, 2.419499f, 1.167008f },
  { -1.353677f, 2.455801f, 0.285458f },
  { -1.380593f, 2.432654f, -0.203207f },
  { -1.167008f, 2.419499f, -0.789935f },
  { -0.285458f, 2.455801f, -1.353677f },
  { 0.111367f, 2.429268f, -1.385776f },
  { 0.740129f, 2.423638f, -1.204645f },
  { 1.092250f, 2.475048f, -0.850606f },
  { 1.287781f, 2.427442f, -0.527881f },
  { 1.369074f, 2.399909f, -0.318540f },
  { 1.268535f, 2.421878f, 0.590029f },
  { 1.222665f, 2.493829f, 0.800945f },
  { 0.868685f, 2.494213f, -1.169803f },
  { 1.322105f, 2.488310f, -0.440962f },
  { 0.548711f, 2.466355f, 1.271486f },
  { -1.215207f, 2.468137f, 0.682962f },
  { -0.682962f, 2.468137f, -1.215207f },
  { 1.465330f, 2.479053f, 0.075311f },
  { 1.378168f, 2.490340f, 0.471924f },
  { -0.246207f, 2.492052f, 1.434504f },
  { -1.434504f, 2.492052f, -0.246208f },
  { 0.246207f, 2.492052f, -1.434504f },
  { 0.471925f, 2.490340f, -1.378168f },
  { 1.368795f, 2.460594f, -0.557351f },
  { 1.460260f, 2.449743f, -0.237719f },
  { 0.932202f, 2.501646f, 1.121886f },
  { 0.677765f, 2.458956f, 1.310601f },
  { 0.465880f, 2.458938f, 1.398211f },
  { 0.237812f, 2.458915f, 1.452624f },
  { -0.000288f, 2.420282f, 1.490257f },
  { -0.483241f, 2.496330f, 1.370113f },
  { -0.882028f, 2.485900f, 1.165854f },
  { -1.138212f, 2.457424f, 0.948938f },
  { -1.368795f, 2.460594f, 0.557351f },
  { -1.452624f, 2.458915f, 0.237812f },
  { -1.370114f, 2.496330f, -0.483241f },
  { -1.165854f, 2.485900f, -0.882028f },
  { -0.948938f, 2.457424f, -1.138212f },
  { -0.557350f, 2.460594f, -1.368796f },
  { -0.237812f, 2.458915f, -1.452624f },
  { 0.000288f, 2.420282f, -1.490257f },
  { -1.514415f, 2.373343f, -0.003415f },
  { 1.098325f, 2.459974f, -0.995512f },
  { -0.549324f, 1.923845f, -1.636194f },
  { -0.797168f, 1.924179f, -1.532901f },
  { -0.282377f, 1.923728f, -1.700560f },
  { 0.000312f, 1.924225f, -1.722484f },
  { 0.282924f, 1.924734f, -1.700023f },
  { 0.549814f, 1.924525f, -1.635720f },
  { 0.791231f, 1.963325f, -1.516871f },
  { 1.394237f, 1.923992f, -1.022831f },
  { 1.532901f, 1.924180f, -0.797168f },
  { 1.636194f, 1.923845f, -0.549325f },
  { 1.700022f, 1.924737f, 0.282925f },
  { 1.635719f, 1.924526f, 0.549813f },
  { 1.532479f, 1.924497f, 0.797683f },
  { 1.393798f, 1.924202f, 1.023280f },
  { 1.222762f, 1.924152f, 1.223214f },
  { 1.022831f, 1.923991f, 1.394237f },
  { 0.797168f, 1.924179f, 1.532901f },
  { 0.549324f, 1.923845f, 1.636194f },
  { 0.282378f, 1.923727f, 1.700560f },
  { -0.000312f, 1.924225f, 1.722484f },
  { -0.282924f, 1.924734f, 1.700023f },
  { -0.549814f, 1.924525f, 1.635720f },
  { -0.791231f, 1.963325f, 1.516871f },
  { -1.023280f, 1.924202f, 1.393798f },
  { -1.223213f, 1.924152f, 1.222763f },
  { -1.394237f, 1.923992f, 1.022831f },
  { -1.532901f, 1.924180f, 0.797168f },
  { -1.636194f, 1.923845f, 0.549325f },
  { -1.700559f, 1.923729f, 0.282377f },
  { -1.700023f, 1.924735f, -0.282925f },
  { -1.635720f, 1.924526f, -0.549813f },
  { -1.516871f, 1.963325f, -0.791231f },
  { -1.393798f, 1.924202f, -1.023280f },
  { -1.222762f, 1.924152f, -1.223214f },
  { -1.022831f, 1.923991f, -1.394237f },
  { 1.049903f, 1.826102f, -1.428941f },
  { -1.114582f, 1.533758f, -1.518070f },
  { -1.332331f, 1.533771f, -1.331750f },
  { -0.868997f, 1.533493f, -1.669330f },
  { -0.598957f, 1.533637f, -1.781775f },
  { -0.308291f, 1.533392f, -1.852011f },
  { -0.000391f, 1.533822f, -1.876099f },
  { 0.307448f, 1.534102f, -1.851894f },
  { 0.598186f, 1.534154f, -1.781840f },
  { 0.868193f, 1.533845f, -1.669605f },
  { 1.304911f, 1.647782f, -1.304616f },
  { 1.814301f, 1.647120f, -0.301415f },
  { 1.837729f, 1.647698f, 0.000210f },
  { 0.000052f, 1.361727f, 1.934353f },
  { -0.317373f, 1.362295f, 1.909275f },
  { -0.617091f, 1.362101f, 1.837071f },
  { -0.895484f, 1.362008f, 1.721194f },
  { -1.148800f, 1.361759f, 1.565457f },
  { -1.373361f, 1.361671f, 1.373441f },
  { -1.565424f, 1.361542f, 1.148948f },
  { -1.721286f, 1.361483f, 0.895630f },
  { -1.837257f, 1.361263f, 0.617293f },
  { -1.909585f, 1.361124f, 0.317540f },
  { -1.837729f, 1.647698f, -0.000210f },
  { -1.851894f, 1.534103f, -0.307448f },
  { -1.781840f, 1.534153f, -0.598186f },
  { -1.669605f, 1.533844f, -0.868194f },
  { -1.518479f, 1.533929f, -1.113919f },
  { 1.141732f, 1.386364f, -1.556506f },
  { -1.601751f, 1.161695f, -1.174798f },
  { -1.761099f, 1.161681f, -0.915585f },
  { -1.405414f, 1.161561f, -1.404540f },
  { -1.175777f, 1.161483f, -1.601088f },
  { -0.916735f, 1.161256f, -1.760599f },
  { -0.631960f, 1.161186f, -1.879290f },
  { -0.325393f, 1.160982f, -1.953348f },
  { -0.000602f, 1.161512f, -1.978850f },
  { 0.324172f, 1.162053f, -1.953342f },
  { 0.630801f, 1.161894f, -1.879532f },
  { 0.915585f, 1.161681f, -1.761099f },
  { 1.418316f, 1.059259f, -1.420276f },
  { 1.565424f, 1.361542f, -1.148948f },
  { 1.721286f, 1.361483f, -0.895630f },
  { 1.837257f, 1.361263f, -0.617293f },
  { 1.935058f, 1.241184f, -0.322203f },
  { 1.960304f, 1.241591f, -0.000486f },
  { 1.909275f, 1.362296f, 0.317373f },
  { 1.837071f, 1.362101f, 0.617091f },
  { 1.721193f, 1.362010f, 0.895484f },
  { 1.565457f, 1.361759f, 1.148800f },
  { 1.373441f, 1.361671f, 1.373361f },
  { 1.148949f, 1.361542f, 1.565424f },
  { 0.895630f, 1.361483f, 1.721286f },
  { 0.617292f, 1.361263f, 1.837257f },
  { 0.317540f, 1.361123f, 1.909585f },
  { -1.978849f, 1.161512f, 0.000602f },
  { -1.953342f, 1.162053f, -0.324172f },
  { -1.879532f, 1.161894f, -0.630801f },
  { 1.186825f, 1.000802f, -1.620949f },
  { 1.621168f, 0.870395f, -1.193076f },
  { 1.783069f, 0.870342f, -0.930684f },
  { 1.900285f, 0.944050f, -0.640898f },
  { 1.975441f, 0.943959f, -0.330822f },
  { 2.001590f, 0.944303f, -0.002363f },
  { 1.976151f, 0.944611f, 0.326181f },
  { 1.901737f, 0.944485f, 0.636392f },
  { 1.782148f, 0.944452f, 0.924587f },
  { 1.621247f, 0.944345f, 1.186856f },
  { 1.422821f, 0.944284f, 1.419436f },
  { 1.190730f, 0.944216f, 1.618431f },
  { 0.930684f, 0.870342f, 1.783069f },
  { 0.640898f, 0.944049f, 1.900285f },
  { 0.330822f, 0.943959f, 1.975441f },
  { 0.002363f, 0.944304f, 2.001590f },
  { -0.326181f, 0.944611f, 1.976151f },
  { -0.636391f, 0.944485f, 1.901737f },
  { -0.924587f, 0.944452f, 1.782148f },
  { -1.186856f, 0.944344f, 1.621247f },
  { -1.419436f, 0.944283f, 1.422821f },
  { -1.618431f, 0.944216f, 1.190730f },
  { -1.780012f, 0.944184f, 0.928787f },
  { -1.903586f, 0.870202f, 0.642298f },
  { -1.975441f, 0.943959f, 0.330822f },
  { -1.972504f, 0.827092f, -0.325926f },
  { -1.964079f, 0.676910f, 0.002721f },
  { -1.898159f, 0.826998f, -0.635551f },
  { -1.778743f, 0.826896f, -0.923160f },
  { -1.618077f, 0.826807f, -1.184936f },
  { -1.419986f, 0.826750f, -1.417033f },
  { -1.188300f, 0.826679f, -1.615610f },
  { -0.926835f, 0.826612f, -1.776827f },
  { -0.639431f, 0.826530f, -1.896839f },
  { -0.329962f, 0.826410f, -1.971790f },
  { -0.002072f, 0.826744f, -1.997900f },
  { 0.325926f, 0.827092f, -1.972504f },
  { 0.635551f, 0.826999f, -1.898159f },
  { 0.923160f, 0.826896f, -1.778743f },
  { 1.864419f, 0.676620f, -0.629272f },
  { 1.938186f, 0.676518f, -0.325055f },
  { 1.964079f, 0.676910f, -0.002721f },
  { 1.939326f, 0.677304f, 0.319803f },
  { 1.866297f, 0.677152f, 0.624180f },
  { 1.767220f, 0.771675f, 0.919439f },
  { 1.598963f, 0.722380f, 1.173603f },
  { 1.297938f, 0.720933f, 1.507480f },
  { 0.629272f, 0.676620f, 1.864419f },
  { 0.325055f, 0.676518f, 1.938186f },
  { 0.002721f, 0.676910f, 1.964079f },
  { -0.319802f, 0.677304f, 1.939326f },
  { -0.624181f, 0.677152f, 1.866297f },
  { -0.906962f, 0.677059f, 1.748972f },
  { -1.164343f, 0.676983f, 1.591105f },
  { -1.392553f, 0.676909f, 1.396439f },
  { -1.587837f, 0.676830f, 1.168731f },
  { -1.746380f, 0.676730f, 0.911751f },
  { -1.938186f, 0.676518f, 0.325055f },
  { -1.882171f, 0.612048f, -0.459774f },
  { -1.717563f, 0.614410f, -0.893863f },
  { -1.477714f, 0.612106f, -1.260983f },
  { -1.146274f, 0.614248f, -1.562191f },
  { -0.893481f, 0.614184f, -1.717629f },
  { -0.615715f, 0.614094f, -1.833203f },
  { -0.317652f, 0.544577f, -1.870650f },
  { 0.000177f, 0.614302f, -1.930254f },
  { 0.317040f, 0.614573f, -1.905483f },
  { 0.616085f, 0.614452f, -1.833277f },
  { 0.893863f, 0.614410f, -1.717563f },
  { 1.164343f, 0.676983f, -1.591105f },
  { 1.392553f, 0.676909f, -1.396439f },
  { 1.647373f, 0.612000f, -1.027685f },
  { 0.887553f, 0.576108f, 1.700495f },
  { -1.798880f, 0.544699f, 0.611223f },
  { 1.702881f, 0.576385f, 0.883249f },
  { 1.531115f, 0.436906f, 0.986288f },
  { 1.199790f, 0.458440f, 1.396513f },
  { -1.533975f, 0.431083f, 0.958569f },
  { -1.795720f, 0.430203f, 0.153383f },
  { -1.753507f, 0.430794f, -0.426793f },
  { -1.540084f, 0.431127f, -0.948674f },
  { -0.709362f, 0.430826f, -1.661902f },
  { 0.140619f, 0.430529f, -1.796999f },
  { 0.575363f, 0.436140f, -1.711003f },
  { 0.948674f, 0.431128f, -1.540084f },
  { 1.576598f, 0.403728f, -0.824884f },
  { 1.796999f, 0.430529f, 0.140619f },
  { 1.711002f, 0.436140f, 0.575363f },
  { -0.140619f, 0.430529f, 1.796999f },
  { -0.686516f, 0.401028f, 1.643410f },
  { -1.050283f, 0.403827f, 1.438056f },
  { -1.256576f, 0.403785f, 1.262407f },
  { -1.167083f, 0.401121f, -1.348924f },
  { 1.342381f, 0.409462f, -1.185770f },
  { 1.727700f, 0.409267f, -0.454439f },
  { 0.671253f, 0.386832f, 1.633214f },
  { 0.295070f, 0.403645f, 1.750309f },
  { -0.987492f, 0.177143f, 1.158048f },
  { -1.289576f, 0.178735f, 0.813472f },
  { -1.436219f, 0.180004f, 0.495175f },
  { -1.513526f, 0.178523f, 0.135645f },
  { -1.498569f, 0.180074f, -0.236873f },
  { -1.407245f, 0.178735f, -0.582835f },
  { -0.603856f, 0.178676f, -1.398464f },
  { -0.260650f, 0.179978f, -1.494690f },
  { 0.112136f, 0.178559f, -1.515395f },
  { 0.472245f, 0.180071f, -1.443779f },
  { 0.856042f, 0.184775f, -1.274520f },
  { 1.219774f, 0.180020f, -0.910374f },
  { 1.397998f, 0.177062f, -0.596007f },
  { 1.494690f, 0.179978f, -0.260650f },
  { 1.515395f, 0.178559f, 0.112137f },
  { 1.443779f, 0.180070f, 0.472245f },
  { 1.227096f, 0.174954f, 0.909158f },
  { 0.805597f, 0.177100f, 1.290332f },
  { 0.368290f, 0.177024f, 1.472572f },
  { -0.182210f, 0.184726f, 1.519642f },
  { -1.120889f, 0.177950f, -1.043906f },
  { -0.437558f, 0.102031f, 1.417043f },
  { 0.242691f, 0.098811f, 1.472203f },
  { 0.083300f, -0.001789f, -0.327834f },
  { -0.344668f, 0.044109f, 1.252696f },
  { -0.967354f, 0.099118f, 1.132744f },
  { -1.327578f, 0.098861f, 0.688384f },
  { -1.080498f, 0.046520f, 0.782754f },
  { -1.454745f, 0.076540f, 0.125507f },
  { -0.958681f, 0.015764f, -0.015385f },
  { -1.237375f, 0.043299f, -0.370108f },
  { -1.430510f, 0.084686f, -0.382585f },
  { -1.122635f, 0.086391f, -0.957237f },
  { -0.687473f, 0.045155f, -1.141890f },
  { -0.585419f, 0.096833f, -1.385825f },
  { -0.327752f, 0.009962f, -0.776183f },
  { 0.236267f, 0.098948f, -1.473381f },
  { 0.119479f, 0.045529f, -1.307737f },
  { 0.273475f, 0.029156f, -1.121093f },
  { 0.751563f, 0.073802f, -1.242924f },
  { 0.919741f, 0.032559f, -0.789479f },
  { 1.133637f, 0.102387f, -0.996861f },
  { 1.409340f, 0.083545f, -0.419612f },
  { 1.299725f, 0.041130f, -0.057300f },
  { 1.461194f, 0.098538f, 0.352753f },
  { 1.136725f, 0.071580f, 0.904526f },
  { 0.742947f, 0.007321f, 0.423864f },
  { 0.794637f, 0.077642f, 1.227133f },
  { 0.245446f, 0.036465f, 1.229315f },
  { -0.489781f, 0.013460f, 0.813130f },
  { -0.320191f, 3.141752f, 0.037750f },
  { 0.398233f, 3.122946f, 0.163785f },
  { 0.278136f, 3.113028f, -0.243275f },
  { -0.341681f, 3.058321f, -0.200182f },
  { 0.022951f, 3.079320f, -0.394586f },
  { 0.090735f, 3.087166f, 0.405932f },
  { -0.356266f, 3.073115f, 0.204784f },
  { -0.088973f, 2.754368f, -0.126120f },
  { 0.164656f, 2.769891f, -0.045884f },
  { 0.080747f, 2.781793f, 0.154691f },
  { -0.141549f, 2.764438f, 0.088836f },
  { 0.137828f, 2.628490f, 0.324934f },
  { 0.147479f, 2.716482f, -0.087189f },
  { -0.351683f, 2.631644f, 0.075230f },
  { -0.185613f, 2.616224f, -0.385242f },
  { 0.251726f, 2.611866f, -0.388192f },
  { 0.477196f, 2.608172f, 0.101924f },
  { -0.195715f, 2.616357f, 0.381143f },
  { -0.559260f, 2.496508f, 1.030063f },
  { -0.720774f, 2.499614f, -0.891991f },
  { 0.503726f, 2.507467f, -0.993433f },
  { 1.037344f, 2.502579f, -0.459940f },
  { 0.992507f, 2.521254f, 0.252339f },
  { 0.692657f, 2.502441f, 0.899017f },
  { 0.103450f, 2.519408f, 1.031145f },
  { -0.246994f, 2.503844f, -1.096312f },
  { -0.979406f, 2.497921f, 0.592669f },
  { -1.027132f, 2.500137f, -0.476842f },
  { -1.202031f, 2.428061f, -0.514552f },
  { 1.242885f, 2.462474f, -0.196077f },
  { -0.927546f, 2.444596f, -0.898053f },
  { -0.511504f, 2.430385f, -1.188108f },
  { -0.014706f, 2.458712f, -1.268196f },
  { 0.482846f, 2.434057f, -1.211574f },
  { 0.835754f, 2.457239f, -0.959609f },
  { 1.130471f, 2.426525f, -0.643870f },
  { 1.268051f, 2.444826f, 0.217383f },
  { 1.078731f, 2.463489f, 0.653590f },
  { 0.982389f, 2.447929f, 0.825369f },
  { 0.602944f, 2.430598f, 1.152281f },
  { 0.130115f, 2.459050f, 1.258068f },
  { -0.400237f, 2.430686f, 1.235863f },
  { -0.914984f, 2.430626f, 0.925667f },
  { -1.231255f, 2.430576f, 0.414842f },
  { -1.223620f, 2.483558f, 0.043521f },
  { -1.598178f, 2.028748f, -0.106756f },
  { -1.594313f, 2.038080f, 0.118662f },
  { -1.565132f, 2.105494f, 0.222062f },
  { -1.513619f, 2.219341f, 0.183846f },
  { -2.332971f, 0.830672f, 0.094025f },
  { -2.525041f, 2.193801f, 0.152099f },
  { -2.185930f, 2.245385f, 0.061939f },
  { -2.873267f, 2.071118f, 0.155393f },
  { -3.008564f, 1.737021f, 0.091558f },
  { -2.872076f, 1.317367f, 0.015283f },
  { -1.902516f, 0.609449f, 0.119205f },
  { -2.660562f, 1.128314f, 0.181030f },
  { -2.789688f, 1.414423f, 0.229602f },
  { -2.836812f, 1.954981f, 0.231198f },
  { -2.615706f, 2.092998f, 0.226619f },
  { -2.152948f, 0.860613f, 0.252002f },
  { -2.362376f, 2.046239f, 0.168792f },
  { -2.540838f, 1.312756f, 0.139940f },
  { -1.968105f, 0.806705f, 0.230664f },
  { -2.252903f, 1.037603f, 0.102132f },
  { -2.716639f, 1.637042f, 0.161564f },
  { -2.566007f, 1.952547f, -0.064309f },
  { -2.706053f, 1.814793f, 0.009312f },
  { -2.743940f, 1.738775f, -0.158282f },
  { -2.000462f, 0.902142f, -0.063566f },
  { -1.948050f, 0.742321f, -0.230564f },
  { -1.909221f, 0.603110f, -0.093661f },
  { -2.324503f, 0.838331f, -0.146798f },
  { -2.728537f, 1.151778f, -0.093890f },
  { -2.947061f, 1.998881f, -0.151577f },
  { -1.503454f, 2.241995f, -0.118842f },
  { -2.676592f, 2.188744f, -0.081914f },
  { -2.409017f, 1.023705f, -0.230360f },
  { -2.950163f, 1.621827f, -0.167210f },
  { -2.347267f, 2.160185f, -0.232818f },
  { -2.783065f, 1.364053f, -0.222432f },
  { -2.855611f, 1.907595f, -0.226518f },
  { -1.547120f, 2.146087f, -0.231683f },
  { -2.566874f, 1.337645f, -0.185664f },
  { -2.241150f, 2.043619f, -0.155283f },
  { -2.293352f, 2.014216f, 0.005044f },
  { -2.322409f, 1.078735f, -0.144723f },
  { 1.700065f, 1.425545f, -0.076273f },
  { 1.939390f, 1.423220f, 0.175100f },
  { 2.028020f, 1.342851f, 0.366832f },
  { 1.700376f, 1.348218f, 0.330643f },
  { 1.700202f, 1.063082f, 0.496462f },
  { 1.700000f, 0.890400f, 0.475200f },
  { 2.049103f, 0.808633f, 0.365659f },
  { 1.700064f, 0.711392f, 0.358773f },
  { 1.699902f, 0.599347f, 0.075027f },
  { 2.063889f, 0.697626f, 0.096718f },
  { 2.318867f, 0.838374f, -0.079245f },
  { 2.495178f, 1.021538f, 0.083608f },
  { 2.637713f, 1.284974f, 0.053407f },
  { 2.812150f, 1.866373f, -0.043107f },
  { 2.937493f, 2.099171f, -0.041092f },
  { 3.104126f, 2.291773f, -0.061647f },
  { 3.069710f, 2.440054f, -0.179763f },
  { 3.009009f, 2.262176f, 0.153563f },
  { 2.532747f, 1.160574f, 0.273376f },
  { 2.310399f, 0.874607f, 0.234526f },
  { 2.778312f, 1.858341f, 0.165629f },
  { 3.342434f, 2.460801f, 0.119035f },
  { 2.824857f, 2.118205f, 0.207843f },
  { 2.483664f, 1.351639f, 0.398044f },
  { 2.268328f, 1.024925f, 0.423407f },
  { 2.067187f, 1.038760f, 0.484690f },
  { 2.063630f, 1.201468f, 0.462000f },
  { 2.704975f, 2.086613f, 0.237331f },
  { 2.956718f, 2.461114f, 0.171845f },
  { 2.206156f, 1.504883f, 0.219243f },
  { 2.379820f, 1.522281f, 0.355736f },
  { 2.603279f, 2.246255f, 0.137306f },
  { 2.396973f, 1.820608f, 0.063506f },
  { 2.020936f, 1.458637f, 0.003077f },
  { 1.720992f, 1.362472f, -0.270804f },
  { 2.170197f, 1.520010f, -0.103994f },
  { 2.294441f, 1.649307f, -0.019676f },
  { 2.427480f, 1.802127f, -0.216068f },
  { 2.555429f, 2.259441f, -0.069475f },
  { 2.727423f, 2.453797f, -0.054784f },
  { 2.616242f, 1.291158f, -0.190673f },
  { 2.054683f, 0.730528f, -0.237597f },
  { 1.699801f, 0.645677f, -0.256118f },
  { 2.033740f, 0.856788f, -0.408568f },
  { 2.475396f, 1.059606f, -0.263014f },
  { 2.509035f, 1.294875f, -0.368791f },
  { 2.777559f, 2.010443f, -0.206339f },
  { 3.056638f, 2.338320f, -0.164904f },
  { 2.277793f, 0.958213f, -0.386340f },
  { 2.004326f, 1.004690f, -0.485123f },
  { 1.699896f, 0.832921f, -0.456334f },
  { 2.686347f, 2.147012f, -0.215849f },
  { 2.306483f, 1.268183f, -0.447528f },
  { 2.262130f, 1.470981f, -0.322981f },
  { 2.032847f, 1.342429f, -0.369148f },
  { 1.700352f, 1.156009f, -0.481739f },
};

Triangle teapot_tris[] = {
  { 12, 13, 18, 0 },
  { 14, 18, 13, 0 },
  { 14, 0, 18, 0 },
  { 15, 1, 30, 0 },
  { 1, 2, 30, 0 },
  { 4, 5, 35, 0 },
  { 7, 8, 40, 0 },
  { 18, 0, 22, 0 },
  { 0, 23, 22, 0 },
  { 0, 15, 23, 0 },
  { 15, 16, 23, 0 },
  { 15, 30, 16, 0 },
  { 2, 19, 30, 0 },
  { 3, 4, 24, 0 },
  { 4, 35, 24, 0 },
  { 35, 5, 36, 0 },
  { 5, 20, 36, 0 },
  { 6, 7, 25, 0 },
  { 7, 40, 25, 0 },
  { 40, 8, 41, 0 },
  { 8, 21, 41, 0 },
  { 9, 10, 26, 0 },
  { 10, 27, 26, 0 },
  { 10, 11, 27, 0 },
  { 11, 17, 27, 0 },
  { 11, 12, 17, 0 },
  { 17, 12, 47, 0 },
  { 12, 28, 47, 0 },
  { 12, 18, 28, 0 },
  { 18, 29, 28, 0 },
  { 18, 22, 29, 0 },
  { 30, 19, 32, 0 },
  { 30, 32, 31, 0 },
  { 19, 3, 33, 0 },
  { 19, 33, 32, 0 },
  { 3, 24, 33, 0 },
  { 36, 20, 37, 0 },
  { 20, 38, 37, 0 },
  { 20, 6, 39, 0 },
  { 20, 39, 38, 0 },
  { 6, 25, 39, 0 },
  { 41, 21, 42, 0 },
  { 21, 43, 42, 0 },
  { 21, 9, 44, 0 },
  { 21, 44, 43, 0 },
  { 9, 26, 44, 0 },
  { 33, 24, 34, 0 },
  { 39, 25, 46, 0 },
  { 44, 26, 45, 0 },
  { 27, 17, 54, 0 },
  { 35, 36, 70, 0 },
  { 40, 41, 79, 0 },
  { 45, 26, 52, 0 },
  { 45, 52, 51, 0 },
  { 26, 27, 53, 0 },
  { 26, 53, 52, 0 },
  { 27, 54, 53, 0 },
  { 54, 17, 83, 0 },
  { 17, 47, 83, 0 },
  { 47, 28, 56, 0 },
  { 47, 56, 55, 0 },
  { 28, 57, 56, 0 },
  { 28, 29, 57, 0 },
  { 22, 23, 59, 0 },
  { 22, 59, 58, 0 },
  { 23, 16, 60, 0 },
  { 23, 60, 59, 0 },
  { 16, 61, 60, 0 },
  { 16, 30, 62, 0 },
  { 16, 62, 61, 0 },
  { 30, 63, 62, 0 },
  { 30, 31, 64, 0 },
  { 30, 64, 63, 0 },
  { 31, 32, 65, 0 },
  { 31, 65, 64, 0 },
  { 32, 33, 66, 0 },
  { 32, 66, 65, 0 },
  { 33, 34, 67, 0 },
  { 33, 67, 66, 0 },
  { 34, 24, 68, 0 },
  { 34, 68, 67, 0 },
  { 24, 35, 69, 0 },
  { 24, 69, 68, 0 },
  { 35, 70, 69, 0 },
  { 70, 36, 71, 0 },
  { 36, 37, 72, 0 },
  { 36, 72, 71, 0 },
  { 37, 73, 72, 0 },
  { 37, 38, 74, 0 },
  { 37, 74, 73, 0 },
  { 38, 75, 74, 0 },
  { 38, 39, 76, 0 },
  { 38, 76, 75, 0 },
  { 39, 46, 76, 0 },
  { 46, 25, 77, 0 },
  { 25, 40, 78, 0 },
  { 25, 78, 77, 0 },
  { 40, 79, 78, 0 },
  { 79, 41, 80, 0 },
  { 41, 42, 81, 0 },
  { 41, 81, 80, 0 },
  { 42, 82, 81, 0 },
  { 42, 43, 49, 0 },
  { 42, 49, 82, 0 },
  { 43, 48, 49, 0 },
  { 43, 44, 50, 0 },
  { 43, 50, 48, 0 },
  { 44, 45, 51, 0 },
  { 44, 51, 50, 0 },
  { 83, 47, 93, 0 },
  { 47, 55, 93, 0 },
  { 57, 29, 94, 0 },
  { 29, 22, 95, 0 },
  { 29, 95, 94, 0 },
  { 22, 58, 95, 0 },
  { 76, 46, 106, 0 },
  { 46, 77, 106, 0 },
  { 82, 49, 86, 0 },
  { 82, 86, 84, 0 },
  { 49, 48, 87, 0 },
  { 49, 87, 86, 0 },
  { 48, 50, 88, 0 },
  { 48, 88, 87, 0 },
  { 50, 51, 89, 0 },
  { 50, 89, 88, 0 },
  { 51, 52, 90, 0 },
  { 51, 90, 89, 0 },
  { 52, 53, 91, 0 },
  { 52, 91, 90, 0 },
  { 53, 54, 92, 0 },
  { 53, 92, 91, 0 },
  { 54, 83, 92, 0 },
  { 93, 55, 124, 0 },
  { 55, 56, 125, 0 },
  { 55, 125, 124, 0 },
  { 56, 57, 126, 0 },
  { 56, 126, 125, 0 },
  { 57, 94, 126, 0 },
  { 95, 58, 129, 0 },
  { 58, 59, 130, 0 },
  { 58, 130, 129, 0 },
  { 59, 60, 131, 0 },
  { 59, 131, 130, 0 },
  { 60, 61, 132, 0 },
  { 60, 132, 131, 0 },
  { 61, 62, 133, 0 },
  { 61, 133, 132, 0 },
  { 62, 63, 134, 0 },
  { 62, 134, 133, 0 },
  { 63, 64, 135, 0 },
  { 63, 135, 134, 0 },
  { 64, 65, 136, 0 },
  { 64, 136, 135, 0 },
  { 65, 66, 137, 0 },
  { 65, 137, 136, 0 },
  { 66, 67, 96, 0 },
  { 66, 96, 137, 0 },
  { 67, 68, 97, 0 },
  { 67, 97, 96, 0 },
  { 68, 69, 98, 0 },
  { 68, 98, 97, 0 },
  { 69, 70, 99, 0 },
  { 69, 99, 98, 0 },
  { 70, 71, 100, 0 },
  { 70, 100, 99, 0 },
  { 71, 72, 101, 0 },
  { 71, 101, 100, 0 },
  { 72, 73, 102, 0 },
  { 72, 102, 101, 0 },
  { 73, 74, 103, 0 },
  { 73, 103, 102, 0 },
  { 74, 75, 104, 0 },
  { 74, 104, 103, 0 },
  { 75, 76, 105, 0 },
  { 75, 105, 104, 0 },
  { 76, 106, 105, 0 },
  { 106, 77, 107, 0 },
  { 77, 78, 108, 0 },
  { 77, 108, 107, 0 },
  { 78, 79, 109, 0 },
  { 78, 109, 108, 0 },
  { 79, 80, 110, 0 },
  { 79, 110, 109, 0 },
  { 80, 81, 85, 0 },
  { 80, 85, 110, 0 },
  { 81, 82, 84, 0 },
  { 81, 84, 85, 0 },
  { 92, 83, 111, 0 },
  { 83, 93, 111, 0 },
  { 110, 85, 114, 0 },
  { 110, 114, 112, 0 },
  { 85, 84, 115, 0 },
  { 85, 115, 114, 0 },
  { 84, 86, 116, 0 },
  { 84, 116, 115, 0 },
  { 86, 87, 117, 0 },
  { 86, 117, 116, 0 },
  { 87, 88, 118, 0 },
  { 87, 118, 117, 0 },
  { 88, 89, 119, 0 },
  { 88, 119, 118, 0 },
  { 89, 90, 120, 0 },
  { 89, 120, 119, 0 },
  { 90, 91, 121, 0 },
  { 90, 121, 120, 0 },
  { 91, 92, 122, 0 },
  { 91, 122, 121, 0 },
  { 92, 111, 122, 0 },
  { 111, 93, 123, 0 },
  { 93, 124, 123, 0 },
  { 126, 94, 127, 0 },
  { 94, 95, 128, 0 },
  { 94, 128, 127, 0 },
  { 95, 129, 128, 0 },
  { 105, 106, 138, 0 },
  { 106, 107, 139, 0 },
  { 106, 139, 138, 0 },
  { 107, 108, 140, 0 },
  { 107, 140, 139, 0 },
  { 108, 109, 113, 0 },
  { 108, 113, 140, 0 },
  { 109, 110, 112, 0 },
  { 109, 112, 113, 0 },
  { 122, 111, 141, 0 },
  { 111, 123, 141, 0 },
  { 123, 124, 142, 0 },
  { 124, 125, 143, 0 },
  { 124, 143, 142, 0 },
  { 125, 126, 144, 0 },
  { 125, 144, 143, 0 },
  { 126, 127, 145, 0 },
  { 126, 145, 144, 0 },
  { 127, 128, 146, 0 },
  { 127, 146, 145, 0 },
  { 128, 129, 147, 0 },
  { 128, 147, 146, 0 },
  { 129, 130, 148, 0 },
  { 129, 148, 147, 0 },
  { 130, 131, 149, 0 },
  { 130, 149, 148, 0 },
  { 131, 132, 150, 0 },
  { 131, 150, 149, 0 },
  { 132, 133, 151, 0 },
  { 132, 151, 150, 0 },
  { 133, 134, 152, 0 },
  { 133, 152, 151, 0 },
  { 134, 135, 153, 0 },
  { 134, 153, 152, 0 },
  { 135, 136, 154, 0 },
  { 135, 154, 153, 0 },
  { 136, 137, 155, 0 },
  { 136, 155, 154, 0 },
  { 137, 96, 156, 0 },
  { 137, 156, 155, 0 },
  { 96, 97, 157, 0 },
  { 96, 157, 156, 0 },
  { 97, 98, 158, 0 },
  { 97, 158, 157, 0 },
  { 98, 99, 159, 0 },
  { 98, 159, 158, 0 },
  { 99, 100, 160, 0 },
  { 99, 160, 159, 0 },
  { 100, 101, 161, 0 },
  { 100, 161, 160, 0 },
  { 101, 102, 162, 0 },
  { 101, 162, 161, 0 },
  { 102, 103, 163, 0 },
  { 102, 163, 162, 0 },
  { 103, 104, 164, 0 },
  { 103, 164, 163, 0 },
  { 104, 105, 165, 0 },
  { 104, 165, 164, 0 },
  { 105, 138, 165, 0 },
  { 139, 140, 168, 0 },
  { 139, 168, 166, 0 },
  { 140, 113, 169, 0 },
  { 140, 169, 168, 0 },
  { 113, 112, 170, 0 },
  { 113, 170, 169, 0 },
  { 112, 114, 171, 0 },
  { 112, 171, 170, 0 },
  { 114, 115, 172, 0 },
  { 114, 172, 171, 0 },
  { 115, 116, 173, 0 },
  { 115, 173, 172, 0 },
  { 116, 117, 174, 0 },
  { 116, 174, 173, 0 },
  { 117, 118, 175, 0 },
  { 117, 175, 174, 0 },
  { 118, 119, 176, 0 },
  { 118, 176, 175, 0 },
  { 119, 120, 177, 0 },
  { 119, 177, 176, 0 },
  { 120, 121, 178, 0 },
  { 120, 178, 177, 0 },
  { 121, 122, 179, 0 },
  { 121, 179, 178, 0 },
  { 122, 141, 179, 0 },
  { 165, 138, 357, 0 },
  { 138, 139, 166, 0 },
  { 138, 166, 357, 0 },
  { 357, 166, 167, 0 },
  { 179, 141, 210, 0 },
  { 141, 123, 211, 0 },
  { 141, 211, 210, 0 },
  { 123, 142, 211, 0 },
  { 143, 144, 180, 0 },
  { 144, 145, 181, 0 },
  { 144, 181, 180, 0 },
  { 145, 146, 182, 0 },
  { 145, 182, 181, 0 },
  { 146, 147, 183, 0 },
  { 146, 183, 182, 0 },
  { 147, 148, 184, 0 },
  { 147, 184, 183, 0 },
  { 148, 149, 185, 0 },
  { 148, 185, 184, 0 },
  { 149, 150, 186, 0 },
  { 149, 186, 185, 0 },
  { 150, 151, 187, 0 },
  { 150, 187, 186, 0 },
  { 151, 152, 187, 0 },
  { 152, 153, 187, 0 },
  { 153, 154, 188, 0 },
  { 154, 155, 189, 0 },
  { 154, 189, 188, 0 },
  { 155, 156, 190, 0 },
  { 155, 190, 189, 0 },
  { 156, 157, 191, 0 },
  { 156, 191, 190, 0 },
  { 157, 158, 192, 0 },
  { 157, 192, 191, 0 },
  { 158, 159, 193, 0 },
  { 158, 193, 192, 0 },
  { 159, 160, 194, 0 },
  { 159, 194, 193, 0 },
  { 160, 161, 195, 0 },
  { 160, 195, 194, 0 },
  { 161, 162, 196, 0 },
  { 161, 196, 195, 0 },
  { 162, 163, 197, 0 },
  { 162, 197, 196, 0 },
  { 163, 164, 197, 0 },
  { 164, 165, 198, 0 },
  { 165, 357, 167, 0 },
  { 165, 167, 198, 0 },
  { 167, 166, 199, 0 },
  { 166, 168, 199, 0 },
  { 168, 169, 200, 0 },
  { 168, 200, 199, 0 },
  { 169, 170, 201, 0 },
  { 169, 201, 200, 0 },
  { 170, 171, 201, 0 },
  { 171, 172, 202, 0 },
  { 171, 202, 201, 0 },
  { 172, 173, 203, 0 },
  { 172, 203, 202, 0 },
  { 173, 174, 204, 0 },
  { 173, 204, 203, 0 },
  { 174, 175, 205, 0 },
  { 174, 205, 204, 0 },
  { 175, 176, 206, 0 },
  { 175, 206, 205, 0 },
  { 176, 177, 207, 0 },
  { 176, 207, 206, 0 },
  { 177, 178, 208, 0 },
  { 177, 208, 207, 0 },
  { 178, 179, 209, 0 },
  { 178, 209, 208, 0 },
  { 179, 210, 209, 0 },
  { 211, 142, 212, 0 },
  { 142, 143, 212, 0 },
  { 143, 180, 212, 0 },
  { 184, 185, 215, 0 },
  { 185, 186, 215, 0 },
  { 187, 153, 213, 0 },
  { 153, 188, 213, 0 },
  { 197, 164, 214, 0 },
  { 164, 198, 214, 0 },
  { 215, 186, 216, 0 },
  { 186, 187, 217, 0 },
  { 186, 217, 216, 0 },
  { 187, 213, 217, 0 },
  { 197, 214, 218, 0 },
  { 214, 198, 219, 0 },
  { 198, 167, 219, 0 },
  { 167, 199, 220, 0 },
  { 167, 220, 219, 0 },
  { 199, 200, 221, 0 },
  { 199, 221, 220, 0 },
  { 200, 201, 221, 0 },
  { 201, 233, 221, 0 },
  { 201, 202, 233, 0 },
  { 202, 203, 222, 0 },
  { 202, 222, 233, 0 },
  { 203, 204, 222, 0 },
  { 204, 205, 222, 0 },
  { 205, 206, 223, 0 },
  { 206, 207, 223, 0 },
  { 207, 208, 224, 0 },
  { 207, 224, 223, 0 },
  { 208, 209, 225, 0 },
  { 208, 225, 224, 0 },
  { 209, 210, 225, 0 },
  { 210, 211, 234, 0 },
  { 210, 234, 225, 0 },
  { 211, 212, 234, 0 },
  { 212, 226, 234, 0 },
  { 212, 180, 235, 0 },
  { 212, 235, 226, 0 },
  { 180, 181, 235, 0 },
  { 181, 182, 227, 0 },
  { 181, 227, 235, 0 },
  { 182, 183, 227, 0 },
  { 183, 184, 228, 0 },
  { 183, 228, 227, 0 },
  { 184, 215, 228, 0 },
  { 213, 188, 236, 0 },
  { 188, 189, 237, 0 },
  { 188, 237, 236, 0 },
  { 189, 190, 229, 0 },
  { 189, 229, 237, 0 },
  { 190, 191, 229, 0 },
  { 191, 192, 230, 0 },
  { 191, 230, 229, 0 },
  { 192, 193, 230, 0 },
  { 193, 194, 231, 0 },
  { 193, 231, 230, 0 },
  { 194, 195, 232, 0 },
  { 194, 232, 231, 0 },
  { 195, 196, 218, 0 },
  { 195, 218, 232, 0 },
  { 196, 197, 218, 0 },
  { 228, 215, 216, 0 },
  { 217, 213, 236, 0 },
  { 232, 218, 239, 0 },
  { 218, 214, 240, 0 },
  { 218, 240, 239, 0 },
  { 214, 219, 241, 0 },
  { 214, 241, 240, 0 },
  { 219, 220, 242, 0 },
  { 219, 242, 241, 0 },
  { 220, 243, 242, 0 },
  { 220, 221, 243, 0 },
  { 221, 258, 243, 0 },
  { 221, 233, 258, 0 },
  { 233, 222, 244, 0 },
  { 222, 205, 245, 0 },
  { 222, 245, 244, 0 },
  { 205, 223, 246, 0 },
  { 205, 246, 245, 0 },
  { 223, 224, 247, 0 },
  { 223, 247, 246, 0 },
  { 224, 225, 248, 0 },
  { 224, 248, 247, 0 },
  { 225, 234, 248, 0 },
  { 234, 226, 249, 0 },
  { 235, 227, 252, 0 },
  { 235, 252, 251, 0 },
  { 227, 228, 253, 0 },
  { 227, 253, 252, 0 },
  { 228, 216, 253, 0 },
  { 237, 229, 257, 0 },
  { 229, 230, 257, 0 },
  { 216, 217, 254, 0 },
  { 230, 231, 238, 0 },
  { 230, 238, 259, 0 },
  { 231, 232, 238, 0 },
  { 232, 239, 238, 0 },
  { 233, 244, 258, 0 },
  { 234, 249, 248, 0 },
  { 249, 226, 250, 0 },
  { 226, 235, 250, 0 },
  { 235, 251, 250, 0 },
  { 253, 216, 254, 0 },
  { 254, 217, 255, 0 },
  { 217, 236, 255, 0 },
  { 236, 256, 255, 0 },
  { 236, 237, 256, 0 },
  { 237, 257, 256, 0 },
  { 230, 259, 257, 0 },
  { 259, 260, 257, 0 },
  { 262, 286, 260, 0 },
  { 262, 260, 259, 0 },
  { 287, 286, 262, 0 },
  { 287, 262, 265, 0 },
  { 265, 262, 259, 0 },
  { 265, 259, 263, 0 },
  { 263, 259, 238, 0 },
  { 261, 284, 287, 0 },
  { 265, 263, 264, 0 },
  { 264, 263, 238, 0 },
  { 264, 238, 239, 0 },
  { 261, 287, 267, 0 },
  { 267, 287, 265, 0 },
  { 264, 239, 240, 0 },
  { 266, 264, 240, 0 },
  { 266, 240, 241, 0 },
  { 266, 265, 264, 0 },
  { 267, 265, 266, 0 },
  { 267, 266, 268, 0 },
  { 268, 266, 269, 0 },
  { 269, 266, 241, 0 },
  { 269, 241, 242, 0 },
  { 269, 242, 243, 0 },
  { 261, 267, 273, 0 },
  { 273, 267, 268, 0 },
  { 273, 268, 271, 0 },
  { 271, 268, 270, 0 },
  { 270, 268, 269, 0 },
  { 270, 269, 243, 0 },
  { 270, 243, 258, 0 },
  { 271, 270, 272, 0 },
  { 272, 270, 258, 0 },
  { 272, 258, 244, 0 },
  { 272, 244, 245, 0 },
  { 273, 271, 275, 0 },
  { 273, 275, 276, 0 },
  { 275, 271, 272, 0 },
  { 275, 272, 274, 0 },
  { 274, 272, 245, 0 },
  { 274, 245, 246, 0 },
  { 274, 246, 247, 0 },
  { 277, 274, 247, 0 },
  { 277, 247, 248, 0 },
  { 277, 275, 274, 0 },
  { 277, 276, 275, 0 },
  { 261, 273, 276, 0 },
  { 261, 276, 278, 0 },
  { 278, 276, 277, 0 },
  { 279, 277, 248, 0 },
  { 278, 277, 279, 0 },
  { 279, 248, 249, 0 },
  { 279, 249, 250, 0 },
  { 280, 278, 279, 0 },
  { 281, 278, 280, 0 },
  { 284, 261, 278, 0 },
  { 284, 278, 281, 0 },
  { 280, 279, 250, 0 },
  { 280, 250, 251, 0 },
  { 281, 280, 282, 0 },
  { 282, 280, 251, 0 },
  { 282, 251, 252, 0 },
  { 282, 252, 253, 0 },
  { 282, 253, 254, 0 },
  { 283, 281, 282, 0 },
  { 284, 281, 283, 0 },
  { 283, 282, 254, 0 },
  { 284, 283, 285, 0 },
  { 285, 283, 254, 0 },
  { 285, 254, 255, 0 },
  { 286, 284, 285, 0 },
  { 287, 284, 286, 0 },
  { 286, 285, 260, 0 },
  { 260, 285, 255, 0 },
  { 260, 255, 256, 0 },
  { 260, 256, 257, 0 },
  { 289, 290, 288, 0 },
  { 289, 288, 293, 0 },
  { 288, 290, 292, 0 },
  { 288, 294, 293, 0 },
  { 294, 288, 291, 0 },
  { 288, 292, 291, 0 },
  { 290, 289, 296, 0 },
  { 291, 292, 295, 0 },
  { 292, 290, 296, 0 },
  { 289, 293, 297, 0 },
  { 289, 297, 296, 0 },
  { 293, 294, 298, 0 },
  { 293, 298, 297, 0 },
  { 294, 291, 298, 0 },
  { 291, 295, 298, 0 },
  { 292, 296, 300, 0 },
  { 292, 300, 295, 0 },
  { 296, 297, 300, 0 },
  { 297, 299, 300, 0 },
  { 297, 298, 299, 0 },
  { 298, 295, 301, 0 },
  { 299, 298, 305, 0 },
  { 298, 301, 305, 0 },
  { 295, 302, 301, 0 },
  { 295, 300, 302, 0 },
  { 300, 303, 302, 0 },
  { 300, 304, 303, 0 },
  { 300, 299, 304, 0 },
  { 301, 302, 315, 0 },
  { 302, 313, 307, 0 },
  { 302, 303, 308, 0 },
  { 302, 308, 313, 0 },
  { 303, 309, 308, 0 },
  { 303, 304, 309, 0 },
  { 304, 310, 309, 0 },
  { 304, 311, 310, 0 },
  { 304, 299, 311, 0 },
  { 299, 312, 311, 0 },
  { 299, 305, 312, 0 },
  { 305, 306, 312, 0 },
  { 305, 301, 306, 0 },
  { 301, 314, 306, 0 },
  { 301, 332, 314, 0 },
  { 301, 315, 332, 0 },
  { 315, 302, 307, 0 },
  { 313, 308, 320, 0 },
  { 308, 309, 322, 0 },
  { 309, 310, 317, 0 },
  { 310, 311, 325, 0 },
  { 312, 306, 328, 0 },
  { 315, 307, 318, 0 },
  { 317, 310, 324, 0 },
  { 310, 325, 324, 0 },
  { 325, 311, 326, 0 },
  { 311, 312, 328, 0 },
  { 315, 318, 316, 0 },
  { 307, 319, 318, 0 },
  { 307, 313, 319, 0 },
  { 313, 320, 319, 0 },
  { 320, 308, 321, 0 },
  { 308, 322, 321, 0 },
  { 322, 309, 323, 0 },
  { 309, 317, 323, 0 },
  { 326, 311, 327, 0 },
  { 311, 328, 327, 0 },
  { 328, 306, 329, 0 },
  { 306, 330, 329, 0 },
  { 306, 314, 330, 0 },
  { 314, 331, 330, 0 },
  { 314, 332, 331, 0 },
  { 332, 315, 316, 0 },
  { 333, 334, 373, 0 },
  { 334, 349, 373, 0 },
  { 334, 335, 349, 0 },
  { 336, 363, 339, 0 },
  { 362, 340, 364, 0 },
  { 342, 341, 366, 0 },
  { 360, 337, 361, 0 },
  { 337, 359, 343, 0 },
  { 337, 360, 359, 0 },
  { 344, 361, 337, 0 },
  { 342, 361, 344, 0 },
  { 340, 362, 341, 0 },
  { 339, 364, 338, 0 },
  { 338, 364, 340, 0 },
  { 348, 337, 343, 0 },
  { 344, 337, 348, 0 },
  { 345, 342, 344, 0 },
  { 345, 341, 342, 0 },
  { 346, 340, 341, 0 },
  { 336, 339, 338, 0 },
  { 336, 338, 347, 0 },
  { 347, 338, 340, 0 },
  { 346, 341, 345, 0 },
  { 348, 343, 351, 0 },
  { 345, 344, 348, 0 },
  { 346, 347, 340, 0 },
  { 335, 336, 347, 0 },
  { 352, 345, 348, 0 },
  { 350, 345, 352, 0 },
  { 353, 345, 350, 0 },
  { 353, 346, 345, 0 },
  { 349, 347, 346, 0 },
  { 335, 347, 349, 0 },
  { 349, 346, 354, 0 },
  { 354, 346, 355, 0 },
  { 355, 346, 353, 0 },
  { 352, 348, 351, 0 },
  { 352, 351, 357, 0 },
  { 373, 349, 354, 0 },
  { 355, 353, 356, 0 },
  { 356, 353, 350, 0 },
  { 356, 350, 371, 0 },
  { 371, 350, 352, 0 },
  { 357, 358, 365, 0 },
  { 358, 360, 365, 0 },
  { 358, 359, 360, 0 },
  { 368, 342, 366, 0 },
  { 366, 341, 362, 0 },
  { 367, 364, 339, 0 },
  { 367, 339, 363, 0 },
  { 368, 361, 342, 0 },
  { 365, 360, 361, 0 },
  { 365, 361, 368, 0 },
  { 366, 362, 369, 0 },
  { 362, 364, 367, 0 },
  { 370, 367, 363, 0 },
  { 369, 362, 367, 0 },
  { 368, 366, 369, 0 },
  { 371, 365, 368, 0 },
  { 368, 369, 356, 0 },
  { 372, 367, 370, 0 },
  { 372, 370, 333, 0 },
  { 354, 367, 372, 0 },
  { 354, 369, 367, 0 },
  { 356, 369, 354, 0 },
  { 356, 371, 368, 0 },
  { 374, 365, 371, 0 },
  { 357, 365, 374, 0 },
  { 356, 354, 355, 0 },
  { 373, 372, 333, 0 },
  { 352, 357, 374, 0 },
  { 352, 374, 371, 0 },
  { 354, 372, 373, 0 },
  { 375, 378, 376, 0 },
  { 378, 377, 376, 0 },
  { 378, 401, 377, 0 },
  { 378, 379, 401, 0 },
  { 379, 400, 401, 0 },
  { 379, 380, 400, 0 },
  { 380, 381, 400, 0 },
  { 380, 382, 381, 0 },
  { 382, 384, 381, 0 },
  { 382, 383, 384, 0 },
  { 416, 384, 383, 0 },
  { 416, 383, 417, 0 },
  { 385, 384, 416, 0 },
  { 419, 386, 385, 0 },
  { 415, 387, 386, 0 },
  { 415, 386, 419, 0 },
  { 415, 388, 387, 0 },
  { 391, 396, 390, 0 },
  { 392, 390, 396, 0 },
  { 389, 390, 392, 0 },
  { 395, 388, 389, 0 },
  { 387, 388, 395, 0 },
  { 386, 387, 393, 0 },
  { 394, 385, 386, 0 },
  { 384, 385, 394, 0 },
  { 381, 384, 394, 0 },
  { 394, 386, 393, 0 },
  { 393, 387, 395, 0 },
  { 395, 389, 397, 0 },
  { 397, 389, 392, 0 },
  { 398, 393, 395, 0 },
  { 399, 394, 393, 0 },
  { 381, 394, 399, 0 },
  { 400, 381, 399, 0 },
  { 399, 393, 398, 0 },
  { 398, 395, 402, 0 },
  { 402, 395, 397, 0 },
  { 403, 392, 396, 0 },
  { 397, 392, 403, 0 },
  { 400, 399, 398, 0 },
  { 401, 400, 398, 0 },
  { 401, 398, 405, 0 },
  { 405, 398, 402, 0 },
  { 402, 397, 403, 0 },
  { 406, 402, 403, 0 },
  { 405, 402, 406, 0 },
  { 377, 401, 405, 0 },
  { 404, 377, 405, 0 },
  { 406, 403, 414, 0 },
  { 407, 406, 413, 0 },
  { 407, 405, 406, 0 },
  { 411, 405, 407, 0 },
  { 411, 404, 405, 0 },
  { 376, 377, 404, 0 },
  { 408, 376, 404, 0 },
  { 375, 376, 408, 0 },
  { 408, 409, 375, 0 },
  { 408, 410, 409, 0 },
  { 407, 412, 411, 0 },
  { 413, 412, 407, 0 },
  { 389, 388, 421, 0 },
  { 421, 388, 415, 0 },
  { 419, 385, 423, 0 },
  { 423, 385, 416, 0 },
  { 418, 416, 417, 0 },
  { 423, 416, 418, 0 },
  { 420, 415, 419, 0 },
  { 421, 415, 420, 0 },
  { 422, 389, 421, 0 },
  { 422, 390, 389, 0 },
  { 391, 390, 422, 0 },
  { 420, 419, 423, 0 },
  { 423, 418, 424, 0 },
  { 424, 418, 425, 0 },
  { 418, 417, 425, 0 },
  { 424, 425, 430, 0 },
  { 427, 423, 424, 0 },
  { 427, 420, 423, 0 },
  { 421, 420, 427, 0 },
  { 426, 422, 421, 0 },
  { 391, 422, 426, 0 },
  { 426, 421, 427, 0 },
  { 427, 424, 430, 0 },
  { 429, 427, 430, 0 },
  { 428, 427, 429, 0 },
  { 412, 427, 428, 0 },
  { 412, 426, 427, 0 },
  { 413, 426, 412, 0 },
  { 414, 426, 413, 0 },
  { 414, 391, 426, 0 },
  { 429, 430, 409, 0 },
  { 410, 429, 409, 0 },
  { 410, 428, 429, 0 },
  { 411, 428, 410, 0 },
  { 412, 428, 411, 0 },
  { 413, 406, 414, 0 },
  { 410, 404, 411, 0 },
  { 408, 404, 410, 0 },
};

Material teapot_mats[1];

Model teapot_model {
  teapot_vertices,
  teapot_tris,
  teapot_mats,
  sizeof(teapot_vertices) / sizeof(teapot_vertices[0]),
  sizeof(teapot_tris) / sizeof(teapot_tris[0]),
  sizeof(teapot_mats) / sizeof(teapot_mats[0])
};

bool teapot_model_inited = false;
}

Model& get_teapot_model() {
  if (!teapot_model_inited) {
    teapot_mats[0] = make_material_for_colour(pimoroni::RGB(200, 200, 255));
    
    set_triangle_normals(teapot_model);
    teapot_model_inited = true;
  }
  
  return teapot_model;
}