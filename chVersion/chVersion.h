// ���� ifdef ���Ǵ���ʹ�� DLL �������򵥵�
// ��ı�׼�������� DLL �е������ļ��������������϶���� CHVERSION_EXPORTS
// ���ű���ġ���ʹ�ô� DLL ��
// �κ�������Ŀ�ϲ�Ӧ����˷��š�������Դ�ļ��а������ļ����κ�������Ŀ���Ὣ
// CHVERSION_API ������Ϊ�Ǵ� DLL ����ģ����� DLL ���ô˺궨���
// ������Ϊ�Ǳ������ġ�
#ifdef CHVERSION_EXPORTS
#define CHVERSION_API __declspec(dllexport)
#else
#define CHVERSION_API __declspec(dllimport)
#endif


// �����Ǵ� chVersion.dll ������
class CHVERSION_API CchVersion {
public:
	CchVersion(void);
	// TODO:  �ڴ�������ķ�����
	//float floatcalculate(float x, float y, int type);
};

extern CHVERSION_API int nchVersion;
extern "C" float __declspec(dllexport) floatcalculate(float x, float y, int type);

CHVERSION_API int fnchVersion(void);
float floatcalculate(float x, float y, int type);