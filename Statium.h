// Statium.h: interface for the CStatium class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_STATIUM_H__D6C3CDE2_09E2_438B_99ED_3EE1B772062A__INCLUDED_)
#define AFX_STATIUM_H__D6C3CDE2_09E2_438B_99ED_3EE1B772062A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#pragma warning (disable:4786)

#include <vector>
#include <string>
#include <map>

#include "Texture.h"
#include "Camera.h"

using namespace std;

struct Vertex
{
	float x,y,z,u,v;
	float r,g,b,a;
	unsigned char uR,uG,uB,uA;
public:
	void Import(FILE *fp);
};

struct Triangle
{
	unsigned int v[3];
public:
	void Import(FILE *fp);
};

class SubMesh
{
public:
	bool Import(string subName,FILE *fp);
	string			Name;		//����
	string			Mat;		//����
	unsigned int	VerNum;		//������
	unsigned int	TriNum;		//��������
	Vertex			*v;			//�����б�
	Triangle		*t;			//�������б�
};

class Mesh
{
public:
	bool Import(FILE *fp);
	string Name;				//����
	unsigned short Num;			//Meshes�е���������
	std::vector<SubMesh> SubMeshes;		//�������б�

};

struct Ad
{
	Vertex v[4];
	int mat;
	float rot;
};

class CStatium  
{
public:
	bool m_bDrawBorder;
	void DrawSelectAds();
	void DrawAdBorder(int i);
	void ExportAds(const char *filename);
	int m_AdNeedToBeDraw;
	void DrawAds(int i);
	bool m_bDrawAdsField;
	void ImportAds(const char *filename);
	//�����i������ƵĻ������
	CString m_szBaseDir;
	void Draw();
	///����.sef������ģ���ļ�
	bool Import(const char *filename);
	CStatium();
	virtual ~CStatium();
	std::map<std::string,CTexture> TextureMap;			//����
	std::vector<Ad> Ads;			//����б�	
private:
	std::vector<Mesh> Meshes;			//�����б�	
	CTexture adsTexture;
	

	bool ImportMeshes(FILE *fp);
	bool ImportMaterial(FILE *fp);
};

#endif // !defined(AFX_STATIUM_H__D6C3CDE2_09E2_438B_99ED_3EE1B772062A__INCLUDED_)
