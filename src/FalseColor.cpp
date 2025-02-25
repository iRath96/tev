/*
 * tev -- the EXR viewer
 *
 * Copyright (C) 2025 Thomas Müller <contact@tom94.net>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <tev/FalseColor.h>

using namespace std;

namespace tev {

namespace colormap {
    const vector<float>& turbo() {
        // "turbo" colormap data generated with scripts/sample-colormap.py
        static const vector<float> data = {
            0.18995f, 0.07176f, 0.23217f, 1.0f,
            0.19483f, 0.08339f, 0.26149f, 1.0f,
            0.19956f, 0.09498f, 0.29024f, 1.0f,
            0.20415f, 0.10652f, 0.31844f, 1.0f,
            0.2086f, 0.11802f, 0.34607f, 1.0f,
            0.21291f, 0.12947f, 0.37314f, 1.0f,
            0.21708f, 0.14087f, 0.39964f, 1.0f,
            0.22111f, 0.15223f, 0.42558f, 1.0f,
            0.225f, 0.16354f, 0.45096f, 1.0f,
            0.22875f, 0.17481f, 0.47578f, 1.0f,
            0.23236f, 0.18603f, 0.50004f, 1.0f,
            0.23582f, 0.1972f, 0.52373f, 1.0f,
            0.23915f, 0.20833f, 0.54686f, 1.0f,
            0.24234f, 0.21941f, 0.56942f, 1.0f,
            0.24539f, 0.23044f, 0.59142f, 1.0f,
            0.2483f, 0.24143f, 0.61286f, 1.0f,
            0.25107f, 0.25237f, 0.63374f, 1.0f,
            0.25369f, 0.26327f, 0.65406f, 1.0f,
            0.25618f, 0.27412f, 0.67381f, 1.0f,
            0.25853f, 0.28492f, 0.693f, 1.0f,
            0.26074f, 0.29568f, 0.71162f, 1.0f,
            0.2628f, 0.30639f, 0.72968f, 1.0f,
            0.26473f, 0.31706f, 0.74718f, 1.0f,
            0.26652f, 0.32768f, 0.76412f, 1.0f,
            0.26816f, 0.33825f, 0.7805f, 1.0f,
            0.26967f, 0.34878f, 0.79631f, 1.0f,
            0.27103f, 0.35926f, 0.81156f, 1.0f,
            0.27226f, 0.3697f, 0.82624f, 1.0f,
            0.27334f, 0.38008f, 0.84037f, 1.0f,
            0.27429f, 0.39043f, 0.85393f, 1.0f,
            0.27509f, 0.40072f, 0.86692f, 1.0f,
            0.27576f, 0.41097f, 0.87936f, 1.0f,
            0.27628f, 0.42118f, 0.89123f, 1.0f,
            0.27667f, 0.43133999999999995f, 0.9025399999999999f, 1.0f,
            0.27691f, 0.44145f, 0.91328f, 1.0f,
            0.27701f, 0.45152f, 0.92347f, 1.0f,
            0.27698f, 0.46153f, 0.93309f, 1.0f,
            0.2768f, 0.47150999999999993f, 0.9421399999999999f, 1.0f,
            0.27648f, 0.48144f, 0.95064f, 1.0f,
            0.27603f, 0.49132f, 0.95857f, 1.0f,
            0.27543f, 0.50115f, 0.96594f, 1.0f,
            0.27469f, 0.5109399999999998f, 0.97275f, 1.0f,
            0.27381f, 0.52069f, 0.97899f, 1.0f,
            0.27273f, 0.5304f, 0.98461f, 1.0f,
            0.27106f, 0.54015f, 0.9893f, 1.0f,
            0.26878f, 0.5499499999999999f, 0.99303f, 1.0f,
            0.26592f, 0.55979f, 0.99583f, 1.0f,
            0.26252f, 0.56967f, 0.99773f, 1.0f,
            0.25862f, 0.57958f, 0.99876f, 1.0f,
            0.25425000000000003f, 0.5894999999999999f, 0.99896f, 1.0f,
            0.24946f, 0.59943f, 0.99835f, 1.0f,
            0.24427f, 0.60937f, 0.99697f, 1.0f,
            0.23874f, 0.61931f, 0.99485f, 1.0f,
            0.23288000000000003f, 0.6292299999999998f, 0.99202f, 1.0f,
            0.22676f, 0.63913f, 0.98851f, 1.0f,
            0.22039f, 0.64901f, 0.98436f, 1.0f,
            0.21382f, 0.65886f, 0.97959f, 1.0f,
            0.20708000000000004f, 0.6686599999999999f, 0.97423f, 1.0f,
            0.20021f, 0.67842f, 0.96833f, 1.0f,
            0.19326f, 0.68812f, 0.9619f, 1.0f,
            0.18625f, 0.69775f, 0.95498f, 1.0f,
            0.17923000000000006f, 0.7073199999999998f, 0.94761f, 1.0f,
            0.17223f, 0.7168f, 0.93981f, 1.0f,
            0.16529f, 0.7262f, 0.93161f, 1.0f,
            0.15844f, 0.73551f, 0.92305f, 1.0f,
            0.15173f, 0.74472f, 0.91416f, 1.0f,
            0.1451900000000001f, 0.7538099999999999f, 0.9049600000000001f, 1.0f,
            0.13886f, 0.76279f, 0.8955f, 1.0f,
            0.13278f, 0.77165f, 0.8858f, 1.0f,
            0.12698f, 0.78037f, 0.8759f, 1.0f,
            0.12151f, 0.78896f, 0.86581f, 1.0f,
            0.11639f, 0.7974f, 0.85559f, 1.0f,
            0.11167f, 0.80569f, 0.84525f, 1.0f,
            0.10738f, 0.81381f, 0.83484f, 1.0f,
            0.10357000000000005f, 0.8217699999999999f, 0.8243700000000002f, 1.0f,
            0.10026f, 0.82955f, 0.81389f, 1.0f,
            0.0975f, 0.83714f, 0.80342f, 1.0f,
            0.09532f, 0.84455f, 0.79299f, 1.0f,
            0.09377f, 0.85175f, 0.78264f, 1.0f,
            0.09287f, 0.85875f, 0.7724f, 1.0f,
            0.09267f, 0.86554f, 0.7623f, 1.0f,
            0.0932f, 0.87211f, 0.75237f, 1.0f,
            0.09450999999999998f, 0.8784399999999999f, 0.7426500000000001f, 1.0f,
            0.09662f, 0.88454f, 0.73316f, 1.0f,
            0.09958f, 0.8904f, 0.72393f, 1.0f,
            0.10342f, 0.896f, 0.715f, 1.0f,
            0.10815f, 0.90142f, 0.70599f, 1.0f,
            0.11374f, 0.90673f, 0.69651f, 1.0f,
            0.12014f, 0.91193f, 0.6866f, 1.0f,
            0.12733f, 0.91701f, 0.67627f, 1.0f,
            0.13525999999999988f, 0.9219699999999998f, 0.6655600000000002f, 1.0f,
            0.14391f, 0.9268f, 0.65448f, 1.0f,
            0.15323f, 0.93151f, 0.64308f, 1.0f,
            0.16319f, 0.93609f, 0.63137f, 1.0f,
            0.17377f, 0.94053f, 0.61938f, 1.0f,
            0.18491f, 0.94484f, 0.60713f, 1.0f,
            0.19659f, 0.94901f, 0.59466f, 1.0f,
            0.20877f, 0.95304f, 0.58199f, 1.0f,
            0.22141999999999984f, 0.95692f, 0.5691400000000002f, 1.0f,
            0.23449f, 0.96065f, 0.55614f, 1.0f,
            0.24797f, 0.96423f, 0.54303f, 1.0f,
            0.2618f, 0.96765f, 0.52981f, 1.0f,
            0.27597f, 0.97092f, 0.51653f, 1.0f,
            0.29042f, 0.97403f, 0.50321f, 1.0f,
            0.30513f, 0.97697f, 0.48987f, 1.0f,
            0.32006f, 0.97974f, 0.47654f, 1.0f,
            0.3351699999999998f, 0.98234f, 0.46325000000000016f, 1.0f,
            0.35043f, 0.98477f, 0.45002f, 1.0f,
            0.36581f, 0.98702f, 0.43688f, 1.0f,
            0.38127f, 0.98909f, 0.42386f, 1.0f,
            0.39678f, 0.99098f, 0.41098f, 1.0f,
            0.41229f, 0.99268f, 0.39826f, 1.0f,
            0.42778f, 0.99419f, 0.38575f, 1.0f,
            0.44321f, 0.99551f, 0.37345f, 1.0f,
            0.4585399999999998f, 0.99663f, 0.36140000000000017f, 1.0f,
            0.47375f, 0.99755f, 0.34963f, 1.0f,
            0.48879f, 0.99828f, 0.33816f, 1.0f,
            0.50362f, 0.99879f, 0.32701f, 1.0f,
            0.51822f, 0.9991f, 0.31622f, 1.0f,
            0.53255f, 0.99919f, 0.30581f, 1.0f,
            0.54658f, 0.99907f, 0.29581f, 1.0f,
            0.56026f, 0.99873f, 0.28623f, 1.0f,
            0.5735699999999998f, 0.99817f, 0.2771200000000001f, 1.0f,
            0.58646f, 0.99739f, 0.26849f, 1.0f,
            0.59891f, 0.99638f, 0.26038f, 1.0f,
            0.61088f, 0.99514f, 0.2528f, 1.0f,
            0.62233f, 0.99366f, 0.24579f, 1.0f,
            0.63323f, 0.99195f, 0.23937f, 1.0f,
            0.64362f, 0.98999f, 0.23356f, 1.0f,
            0.65394f, 0.98775f, 0.22835f, 1.0f,
            0.66428f, 0.98524f, 0.2237f, 1.0f,
            0.67462f, 0.98246f, 0.2196f, 1.0f,
            0.6849399999999997f, 0.9794100000000001f, 0.2160200000000001f, 1.0f,
            0.69525f, 0.9761f, 0.21294f, 1.0f,
            0.70553f, 0.97255f, 0.21032f, 1.0f,
            0.71577f, 0.96875f, 0.20815f, 1.0f,
            0.72596f, 0.9647f, 0.2064f, 1.0f,
            0.7361f, 0.96043f, 0.20504f, 1.0f,
            0.74617f, 0.95593f, 0.20406f, 1.0f,
            0.75617f, 0.95121f, 0.20343f, 1.0f,
            0.76608f, 0.94627f, 0.20311f, 1.0f,
            0.77591f, 0.94113f, 0.2031f, 1.0f,
            0.78563f, 0.93579f, 0.20336f, 1.0f,
            0.79524f, 0.93025f, 0.20386f, 1.0f,
            0.80473f, 0.92452f, 0.20459f, 1.0f,
            0.8141f, 0.91861f, 0.20552f, 1.0f,
            0.82333f, 0.91253f, 0.20663f, 1.0f,
            0.83241f, 0.90627f, 0.20788f, 1.0f,
            0.8413299999999998f, 0.8998600000000002f, 0.20925999999999997f, 1.0f,
            0.8501f, 0.89328f, 0.21074f, 1.0f,
            0.85868f, 0.88655f, 0.2123f, 1.0f,
            0.86709f, 0.87968f, 0.21391f, 1.0f,
            0.8753f, 0.87267f, 0.21555f, 1.0f,
            0.88331f, 0.86553f, 0.21719f, 1.0f,
            0.89112f, 0.85826f, 0.2188f, 1.0f,
            0.8987f, 0.85087f, 0.22038f, 1.0f,
            0.90605f, 0.84337f, 0.22188f, 1.0f,
            0.91317f, 0.83576f, 0.22328f, 1.0f,
            0.92004f, 0.82806f, 0.22456f, 1.0f,
            0.92666f, 0.82025f, 0.2257f, 1.0f,
            0.93301f, 0.81236f, 0.22667f, 1.0f,
            0.93909f, 0.80439f, 0.22744f, 1.0f,
            0.94489f, 0.79634f, 0.228f, 1.0f,
            0.95039f, 0.78823f, 0.22831f, 1.0f,
            0.9555999999999999f, 0.7800500000000002f, 0.22836f, 1.0f,
            0.96049f, 0.77181f, 0.22811f, 1.0f,
            0.96507f, 0.76352f, 0.22754f, 1.0f,
            0.96931f, 0.75519f, 0.22663f, 1.0f,
            0.97323f, 0.74682f, 0.22536f, 1.0f,
            0.97679f, 0.73842f, 0.22369f, 1.0f,
            0.98f, 0.73f, 0.22161f, 1.0f,
            0.98289f, 0.7214f, 0.21918f, 1.0f,
            0.98549f, 0.7125f, 0.2165f, 1.0f,
            0.98781f, 0.7033f, 0.21358f, 1.0f,
            0.98986f, 0.69382f, 0.21043f, 1.0f,
            0.99163f, 0.68408f, 0.20706f, 1.0f,
            0.99314f, 0.67408f, 0.20348f, 1.0f,
            0.99438f, 0.66386f, 0.19971f, 1.0f,
            0.99535f, 0.65341f, 0.19577f, 1.0f,
            0.99607f, 0.64277f, 0.19165f, 1.0f,
            0.99654f, 0.6319300000000003f, 0.1873800000000001f, 1.0f,
            0.99675f, 0.62093f, 0.18297f, 1.0f,
            0.99672f, 0.60977f, 0.17842f, 1.0f,
            0.99644f, 0.59846f, 0.17376f, 1.0f,
            0.99593f, 0.58703f, 0.16899f, 1.0f,
            0.99517f, 0.57549f, 0.16412f, 1.0f,
            0.99419f, 0.56386f, 0.15918f, 1.0f,
            0.99297f, 0.55214f, 0.15417f, 1.0f,
            0.99153f, 0.54036f, 0.1491f, 1.0f,
            0.98987f, 0.52854f, 0.14398f, 1.0f,
            0.98799f, 0.51667f, 0.13883f, 1.0f,
            0.9859f, 0.50479f, 0.13367f, 1.0f,
            0.9836f, 0.49291f, 0.12849f, 1.0f,
            0.98108f, 0.48104f, 0.12332f, 1.0f,
            0.97837f, 0.4692f, 0.11817f, 1.0f,
            0.97545f, 0.4574f, 0.11305f, 1.0f,
            0.9723400000000001f, 0.4456500000000003f, 0.10797000000000014f, 1.0f,
            0.96904f, 0.43399f, 0.10294f, 1.0f,
            0.96555f, 0.42241f, 0.09798f, 1.0f,
            0.96187f, 0.41093f, 0.0931f, 1.0f,
            0.95801f, 0.39958f, 0.08831f, 1.0f,
            0.95398f, 0.38836f, 0.08362f, 1.0f,
            0.94977f, 0.37729f, 0.07905f, 1.0f,
            0.94538f, 0.36638f, 0.07461f, 1.0f,
            0.94084f, 0.35566f, 0.07031f, 1.0f,
            0.93612f, 0.34513f, 0.06616f, 1.0f,
            0.93125f, 0.33482f, 0.06218f, 1.0f,
            0.92623f, 0.32473f, 0.05837f, 1.0f,
            0.92105f, 0.31489f, 0.05475f, 1.0f,
            0.91572f, 0.3053f, 0.05134f, 1.0f,
            0.91024f, 0.29599f, 0.04814f, 1.0f,
            0.90463f, 0.28696f, 0.04516f, 1.0f,
            0.8988800000000001f, 0.2782400000000002f, 0.04243000000000008f, 1.0f,
            0.89298f, 0.26981f, 0.03993f, 1.0f,
            0.88691f, 0.26152f, 0.03753f, 1.0f,
            0.88066f, 0.25334f, 0.03521f, 1.0f,
            0.87422f, 0.24526f, 0.03297f, 1.0f,
            0.8676f, 0.2373f, 0.03082f, 1.0f,
            0.86079f, 0.22945f, 0.02875f, 1.0f,
            0.8538f, 0.2217f, 0.02677f, 1.0f,
            0.84662f, 0.21407f, 0.02487f, 1.0f,
            0.83926f, 0.20654f, 0.02305f, 1.0f,
            0.83172f, 0.19912f, 0.02131f, 1.0f,
            0.82399f, 0.19182f, 0.01966f, 1.0f,
            0.81608f, 0.18462f, 0.01809f, 1.0f,
            0.80799f, 0.17753f, 0.0166f, 1.0f,
            0.79971f, 0.17055f, 0.0152f, 1.0f,
            0.79125f, 0.16368f, 0.01387f, 1.0f,
            0.7826000000000002f, 0.15693000000000018f, 0.012640000000000035f, 1.0f,
            0.77377f, 0.15028f, 0.01148f, 1.0f,
            0.76476f, 0.14374f, 0.01041f, 1.0f,
            0.75556f, 0.13731f, 0.00942f, 1.0f,
            0.74617f, 0.13098f, 0.00851f, 1.0f,
            0.73661f, 0.12477f, 0.00769f, 1.0f,
            0.72686f, 0.11867f, 0.00695f, 1.0f,
            0.71692f, 0.11268f, 0.00629f, 1.0f,
            0.7068f, 0.1068f, 0.00571f, 1.0f,
            0.6965f, 0.10102f, 0.00522f, 1.0f,
            0.68602f, 0.09536f, 0.00481f, 1.0f,
            0.67535f, 0.0898f, 0.00449f, 1.0f,
            0.66449f, 0.08436f, 0.00424f, 1.0f,
            0.65345f, 0.07902f, 0.00408f, 1.0f,
            0.64223f, 0.0738f, 0.00401f, 1.0f,
            0.63082f, 0.06868f, 0.00401f, 1.0f,
            0.6192300000000003f, 0.06367000000000014f, 0.004099999999999998f, 1.0f,
            0.60746f, 0.05878f, 0.00427f, 1.0f,
            0.5955f, 0.05399f, 0.00453f, 1.0f,
            0.58336f, 0.04931f, 0.00486f, 1.0f,
            0.57103f, 0.04474f, 0.00529f, 1.0f,
            0.55852f, 0.04028f, 0.00579f, 1.0f,
            0.54583f, 0.03593f, 0.00638f, 1.0f,
            0.53295f, 0.03169f, 0.00705f, 1.0f,
            0.51989f, 0.02756f, 0.0078f, 1.0f,
            0.50664f, 0.02354f, 0.00863f, 1.0f,
            0.49321f, 0.01963f, 0.00955f, 1.0f,
            0.4796f, 0.01583f, 0.01055f, 1.0f,
        };

        return data;
    }

    const vector<float>& viridis() {
        // "viridis" colormap data generated with scripts/sample-colormap.py
        static const vector<float> data = {
            0.267004f, 0.004874f, 0.329415f, 1.0f,
            0.26851f, 0.009605f, 0.335427f, 1.0f,
            0.269944f, 0.014625f, 0.341379f, 1.0f,
            0.271305f, 0.019942f, 0.347269f, 1.0f,
            0.272594f, 0.025563f, 0.353093f, 1.0f,
            0.273809f, 0.031497f, 0.358853f, 1.0f,
            0.274952f, 0.037752f, 0.364543f, 1.0f,
            0.276022f, 0.044167f, 0.370164f, 1.0f,
            0.277018f, 0.050344f, 0.375715f, 1.0f,
            0.277941f, 0.056324f, 0.381191f, 1.0f,
            0.278791f, 0.062145f, 0.386592f, 1.0f,
            0.279566f, 0.067836f, 0.391917f, 1.0f,
            0.280267f, 0.073417f, 0.397163f, 1.0f,
            0.280894f, 0.078907f, 0.402329f, 1.0f,
            0.281446f, 0.08432f, 0.407414f, 1.0f,
            0.281924f, 0.089666f, 0.412415f, 1.0f,
            0.282327f, 0.094955f, 0.417331f, 1.0f,
            0.282656f, 0.100196f, 0.42216f, 1.0f,
            0.28291f, 0.105393f, 0.426902f, 1.0f,
            0.283091f, 0.110553f, 0.431554f, 1.0f,
            0.283197f, 0.11568f, 0.436115f, 1.0f,
            0.283229f, 0.120777f, 0.440584f, 1.0f,
            0.283187f, 0.125848f, 0.44496f, 1.0f,
            0.283072f, 0.130895f, 0.449241f, 1.0f,
            0.282884f, 0.13592f, 0.453427f, 1.0f,
            0.282623f, 0.140926f, 0.457517f, 1.0f,
            0.28229f, 0.145912f, 0.46151f, 1.0f,
            0.281887f, 0.150881f, 0.465405f, 1.0f,
            0.281412f, 0.155834f, 0.469201f, 1.0f,
            0.280868f, 0.160771f, 0.472899f, 1.0f,
            0.280255f, 0.165693f, 0.476498f, 1.0f,
            0.279574f, 0.170599f, 0.479997f, 1.0f,
            0.278826f, 0.17549f, 0.483397f, 1.0f,
            0.278012f, 0.180367f, 0.486697f, 1.0f,
            0.277134f, 0.185228f, 0.489898f, 1.0f,
            0.276194f, 0.190074f, 0.493001f, 1.0f,
            0.275191f, 0.194905f, 0.496005f, 1.0f,
            0.274128f, 0.199721f, 0.498911f, 1.0f,
            0.273006f, 0.20452f, 0.501721f, 1.0f,
            0.271828f, 0.209303f, 0.504434f, 1.0f,
            0.270595f, 0.214069f, 0.507052f, 1.0f,
            0.269308f, 0.218818f, 0.509577f, 1.0f,
            0.267968f, 0.223549f, 0.512008f, 1.0f,
            0.26658f, 0.228262f, 0.514349f, 1.0f,
            0.265145f, 0.232956f, 0.516599f, 1.0f,
            0.263663f, 0.237631f, 0.518762f, 1.0f,
            0.262138f, 0.242286f, 0.520837f, 1.0f,
            0.260571f, 0.246922f, 0.522828f, 1.0f,
            0.258965f, 0.251537f, 0.524736f, 1.0f,
            0.257322f, 0.25613f, 0.526563f, 1.0f,
            0.255645f, 0.260703f, 0.528312f, 1.0f,
            0.253935f, 0.265254f, 0.529983f, 1.0f,
            0.252194f, 0.269783f, 0.531579f, 1.0f,
            0.250425f, 0.27429f, 0.533103f, 1.0f,
            0.248629f, 0.278775f, 0.534556f, 1.0f,
            0.246811f, 0.283237f, 0.535941f, 1.0f,
            0.244972f, 0.287675f, 0.53726f, 1.0f,
            0.243113f, 0.292092f, 0.538516f, 1.0f,
            0.241237f, 0.296485f, 0.539709f, 1.0f,
            0.239346f, 0.300855f, 0.540844f, 1.0f,
            0.237441f, 0.305202f, 0.541921f, 1.0f,
            0.235526f, 0.309527f, 0.542944f, 1.0f,
            0.233603f, 0.313828f, 0.543914f, 1.0f,
            0.231674f, 0.318106f, 0.544834f, 1.0f,
            0.229739f, 0.322361f, 0.545706f, 1.0f,
            0.227802f, 0.326594f, 0.546532f, 1.0f,
            0.225863f, 0.330805f, 0.547314f, 1.0f,
            0.223925f, 0.334994f, 0.548053f, 1.0f,
            0.221989f, 0.339161f, 0.548752f, 1.0f,
            0.220057f, 0.343307f, 0.549413f, 1.0f,
            0.21813f, 0.347432f, 0.550038f, 1.0f,
            0.21621f, 0.351535f, 0.550627f, 1.0f,
            0.214298f, 0.355619f, 0.551184f, 1.0f,
            0.212395f, 0.359683f, 0.55171f, 1.0f,
            0.210503f, 0.363727f, 0.552206f, 1.0f,
            0.208623f, 0.367752f, 0.552675f, 1.0f,
            0.206756f, 0.371758f, 0.553117f, 1.0f,
            0.204903f, 0.375746f, 0.553533f, 1.0f,
            0.203063f, 0.379716f, 0.553925f, 1.0f,
            0.201239f, 0.38367f, 0.554294f, 1.0f,
            0.19943f, 0.387607f, 0.554642f, 1.0f,
            0.197636f, 0.391528f, 0.554969f, 1.0f,
            0.19586f, 0.395433f, 0.555276f, 1.0f,
            0.1941f, 0.399323f, 0.555565f, 1.0f,
            0.192357f, 0.403199f, 0.555836f, 1.0f,
            0.190631f, 0.407061f, 0.556089f, 1.0f,
            0.188923f, 0.41091f, 0.556326f, 1.0f,
            0.187231f, 0.414746f, 0.556547f, 1.0f,
            0.185556f, 0.41857f, 0.556753f, 1.0f,
            0.183898f, 0.422383f, 0.556944f, 1.0f,
            0.182256f, 0.426184f, 0.55712f, 1.0f,
            0.180629f, 0.429975f, 0.557282f, 1.0f,
            0.179019f, 0.433756f, 0.55743f, 1.0f,
            0.177423f, 0.437527f, 0.557565f, 1.0f,
            0.175841f, 0.44129f, 0.557685f, 1.0f,
            0.174274f, 0.445044f, 0.557792f, 1.0f,
            0.172719f, 0.448791f, 0.557885f, 1.0f,
            0.171176f, 0.45253f, 0.557965f, 1.0f,
            0.169646f, 0.456262f, 0.55803f, 1.0f,
            0.168126f, 0.459988f, 0.558082f, 1.0f,
            0.166617f, 0.463708f, 0.558119f, 1.0f,
            0.165117f, 0.467423f, 0.558141f, 1.0f,
            0.163625f, 0.471133f, 0.558148f, 1.0f,
            0.162142f, 0.474838f, 0.55814f, 1.0f,
            0.160665f, 0.47854f, 0.558115f, 1.0f,
            0.159194f, 0.482237f, 0.558073f, 1.0f,
            0.157729f, 0.485932f, 0.558013f, 1.0f,
            0.15627f, 0.489624f, 0.557936f, 1.0f,
            0.154815f, 0.493313f, 0.55784f, 1.0f,
            0.153364f, 0.497f, 0.557724f, 1.0f,
            0.151918f, 0.500685f, 0.557587f, 1.0f,
            0.150476f, 0.504369f, 0.55743f, 1.0f,
            0.149039f, 0.508051f, 0.55725f, 1.0f,
            0.147607f, 0.511733f, 0.557049f, 1.0f,
            0.14618f, 0.515413f, 0.556823f, 1.0f,
            0.144759f, 0.519093f, 0.556572f, 1.0f,
            0.143343f, 0.522773f, 0.556295f, 1.0f,
            0.141935f, 0.526453f, 0.555991f, 1.0f,
            0.140536f, 0.530132f, 0.555659f, 1.0f,
            0.139147f, 0.533812f, 0.555298f, 1.0f,
            0.13777f, 0.537492f, 0.554906f, 1.0f,
            0.136408f, 0.541173f, 0.554483f, 1.0f,
            0.135066f, 0.544853f, 0.554029f, 1.0f,
            0.133743f, 0.548535f, 0.553541f, 1.0f,
            0.132444f, 0.552216f, 0.553018f, 1.0f,
            0.131172f, 0.555899f, 0.552459f, 1.0f,
            0.129933f, 0.559582f, 0.551864f, 1.0f,
            0.128729f, 0.563265f, 0.551229f, 1.0f,
            0.127568f, 0.566949f, 0.550556f, 1.0f,
            0.126453f, 0.570633f, 0.549841f, 1.0f,
            0.125394f, 0.574318f, 0.549086f, 1.0f,
            0.124395f, 0.578002f, 0.548287f, 1.0f,
            0.123463f, 0.581687f, 0.547445f, 1.0f,
            0.122606f, 0.585371f, 0.546557f, 1.0f,
            0.121831f, 0.589055f, 0.545623f, 1.0f,
            0.121148f, 0.592739f, 0.544641f, 1.0f,
            0.120565f, 0.596422f, 0.543611f, 1.0f,
            0.120092f, 0.600104f, 0.54253f, 1.0f,
            0.119738f, 0.603785f, 0.5414f, 1.0f,
            0.119512f, 0.607464f, 0.540218f, 1.0f,
            0.119423f, 0.611141f, 0.538982f, 1.0f,
            0.119483f, 0.614817f, 0.537692f, 1.0f,
            0.119699f, 0.61849f, 0.536347f, 1.0f,
            0.120081f, 0.622161f, 0.534946f, 1.0f,
            0.120638f, 0.625828f, 0.533488f, 1.0f,
            0.12138f, 0.629492f, 0.531973f, 1.0f,
            0.122312f, 0.633153f, 0.530398f, 1.0f,
            0.123444f, 0.636809f, 0.528763f, 1.0f,
            0.12478f, 0.640461f, 0.527068f, 1.0f,
            0.126326f, 0.644107f, 0.525311f, 1.0f,
            0.128087f, 0.647749f, 0.523491f, 1.0f,
            0.130067f, 0.651384f, 0.521608f, 1.0f,
            0.132268f, 0.655014f, 0.519661f, 1.0f,
            0.134692f, 0.658636f, 0.517649f, 1.0f,
            0.137339f, 0.662252f, 0.515571f, 1.0f,
            0.14021f, 0.665859f, 0.513427f, 1.0f,
            0.143303f, 0.669459f, 0.511215f, 1.0f,
            0.146616f, 0.67305f, 0.508936f, 1.0f,
            0.150148f, 0.676631f, 0.506589f, 1.0f,
            0.153894f, 0.680203f, 0.504172f, 1.0f,
            0.157851f, 0.683765f, 0.501686f, 1.0f,
            0.162016f, 0.687316f, 0.499129f, 1.0f,
            0.166383f, 0.690856f, 0.496502f, 1.0f,
            0.170948f, 0.694384f, 0.493803f, 1.0f,
            0.175707f, 0.6979f, 0.491033f, 1.0f,
            0.180653f, 0.701402f, 0.488189f, 1.0f,
            0.185783f, 0.704891f, 0.485273f, 1.0f,
            0.19109f, 0.708366f, 0.482284f, 1.0f,
            0.196571f, 0.711827f, 0.479221f, 1.0f,
            0.202219f, 0.715272f, 0.476084f, 1.0f,
            0.20803f, 0.718701f, 0.472873f, 1.0f,
            0.214f, 0.722114f, 0.469588f, 1.0f,
            0.220124f, 0.725509f, 0.466226f, 1.0f,
            0.226397f, 0.728888f, 0.462789f, 1.0f,
            0.232815f, 0.732247f, 0.459277f, 1.0f,
            0.239374f, 0.735588f, 0.455688f, 1.0f,
            0.24607f, 0.73891f, 0.452024f, 1.0f,
            0.252899f, 0.742211f, 0.448284f, 1.0f,
            0.259857f, 0.745492f, 0.444467f, 1.0f,
            0.266941f, 0.748751f, 0.440573f, 1.0f,
            0.274149f, 0.751988f, 0.436601f, 1.0f,
            0.281477f, 0.755203f, 0.432552f, 1.0f,
            0.288921f, 0.758394f, 0.428426f, 1.0f,
            0.296479f, 0.761561f, 0.424223f, 1.0f,
            0.304148f, 0.764704f, 0.419943f, 1.0f,
            0.311925f, 0.767822f, 0.415586f, 1.0f,
            0.319809f, 0.770914f, 0.411152f, 1.0f,
            0.327796f, 0.77398f, 0.40664f, 1.0f,
            0.335885f, 0.777018f, 0.402049f, 1.0f,
            0.344074f, 0.780029f, 0.397381f, 1.0f,
            0.35236f, 0.783011f, 0.392636f, 1.0f,
            0.360741f, 0.785964f, 0.387814f, 1.0f,
            0.369214f, 0.788888f, 0.382914f, 1.0f,
            0.377779f, 0.791781f, 0.377939f, 1.0f,
            0.386433f, 0.794644f, 0.372886f, 1.0f,
            0.395174f, 0.797475f, 0.367757f, 1.0f,
            0.404001f, 0.800275f, 0.362552f, 1.0f,
            0.412913f, 0.803041f, 0.357269f, 1.0f,
            0.421908f, 0.805774f, 0.35191f, 1.0f,
            0.430983f, 0.808473f, 0.346476f, 1.0f,
            0.440137f, 0.811138f, 0.340967f, 1.0f,
            0.449368f, 0.813768f, 0.335384f, 1.0f,
            0.458674f, 0.816363f, 0.329727f, 1.0f,
            0.468053f, 0.818921f, 0.323998f, 1.0f,
            0.477504f, 0.821444f, 0.318195f, 1.0f,
            0.487026f, 0.823929f, 0.312321f, 1.0f,
            0.496615f, 0.826376f, 0.306377f, 1.0f,
            0.506271f, 0.828786f, 0.300362f, 1.0f,
            0.515992f, 0.831158f, 0.294279f, 1.0f,
            0.525776f, 0.833491f, 0.288127f, 1.0f,
            0.535621f, 0.835785f, 0.281908f, 1.0f,
            0.545524f, 0.838039f, 0.275626f, 1.0f,
            0.555484f, 0.840254f, 0.269281f, 1.0f,
            0.565498f, 0.84243f, 0.262877f, 1.0f,
            0.575563f, 0.844566f, 0.256415f, 1.0f,
            0.585678f, 0.846661f, 0.249897f, 1.0f,
            0.595839f, 0.848717f, 0.243329f, 1.0f,
            0.606045f, 0.850733f, 0.236712f, 1.0f,
            0.616293f, 0.852709f, 0.230052f, 1.0f,
            0.626579f, 0.854645f, 0.223353f, 1.0f,
            0.636902f, 0.856542f, 0.21662f, 1.0f,
            0.647257f, 0.8584f, 0.209861f, 1.0f,
            0.657642f, 0.860219f, 0.203082f, 1.0f,
            0.668054f, 0.861999f, 0.196293f, 1.0f,
            0.678489f, 0.863742f, 0.189503f, 1.0f,
            0.688944f, 0.865448f, 0.182725f, 1.0f,
            0.699415f, 0.867117f, 0.175971f, 1.0f,
            0.709898f, 0.868751f, 0.169257f, 1.0f,
            0.720391f, 0.87035f, 0.162603f, 1.0f,
            0.730889f, 0.871916f, 0.156029f, 1.0f,
            0.741388f, 0.873449f, 0.149561f, 1.0f,
            0.751884f, 0.874951f, 0.143228f, 1.0f,
            0.762373f, 0.876424f, 0.137064f, 1.0f,
            0.772852f, 0.877868f, 0.131109f, 1.0f,
            0.783315f, 0.879285f, 0.125405f, 1.0f,
            0.79376f, 0.880678f, 0.120005f, 1.0f,
            0.804182f, 0.882046f, 0.114965f, 1.0f,
            0.814576f, 0.883393f, 0.110347f, 1.0f,
            0.82494f, 0.88472f, 0.106217f, 1.0f,
            0.83527f, 0.886029f, 0.102646f, 1.0f,
            0.845561f, 0.887322f, 0.099702f, 1.0f,
            0.85581f, 0.888601f, 0.097452f, 1.0f,
            0.866013f, 0.889868f, 0.095953f, 1.0f,
            0.876168f, 0.891125f, 0.09525f, 1.0f,
            0.886271f, 0.892374f, 0.095374f, 1.0f,
            0.89632f, 0.893616f, 0.096335f, 1.0f,
            0.906311f, 0.894855f, 0.098125f, 1.0f,
            0.916242f, 0.896091f, 0.100717f, 1.0f,
            0.926106f, 0.89733f, 0.104071f, 1.0f,
            0.935904f, 0.89857f, 0.108131f, 1.0f,
            0.945636f, 0.899815f, 0.112838f, 1.0f,
            0.9553f, 0.901065f, 0.118128f, 1.0f,
            0.964894f, 0.902323f, 0.123941f, 1.0f,
            0.974417f, 0.90359f, 0.130215f, 1.0f,
            0.983868f, 0.904867f, 0.136897f, 1.0f,
            0.993248f, 0.906157f, 0.143936f, 1.0f,
        };

        return data;
    }
}

}
