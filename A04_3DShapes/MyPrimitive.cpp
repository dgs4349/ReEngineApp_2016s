#include "MyPrimitive.h"
MyPrimitive::MyPrimitive() { }
MyPrimitive::MyPrimitive(const MyPrimitive& other) { }
MyPrimitive& MyPrimitive::operator=(const MyPrimitive& other) { return *this; }
MyPrimitive::~MyPrimitive(void) { super::Release(); }
void MyPrimitive::CompileObject(vector3 a_v3Color)
{
	m_uVertexCount = static_cast<int> (m_lVertexPos.size());
	for (uint i = 0; i < m_uVertexCount; i++)
	{
		AddVertexColor(a_v3Color);
	}
	
	CompleteTriangleInfo(true);
	CompileOpenGL3X();

}
//C--D
//|\ |
//| \|
//A--B
//This will make the triang A->B->C and then the triang C->B->D
void MyPrimitive::AddQuad(vector3 a_vBottomLeft, vector3 a_vBottomRight, vector3 a_vTopLeft, vector3 a_vTopRight)
{
	AddVertexPosition(a_vBottomLeft);
	AddVertexPosition(a_vBottomRight);
	AddVertexPosition(a_vTopLeft);

	AddVertexPosition(a_vTopLeft);
	AddVertexPosition(a_vBottomRight);
	AddVertexPosition(a_vTopRight);
}
void MyPrimitive::GeneratePlane(float a_fSize, vector3 a_v3Color)
{
	if (a_fSize < 0.01f)
		a_fSize = 0.01f;

	Release();
	Init();

	float fValue = 0.5f * a_fSize;

	vector3 pointA(-fValue, -fValue, 0.0f); //0
	vector3 pointB(fValue, -fValue, 0.0f); //1
	vector3 pointC(fValue, fValue, 0.0f); //2
	vector3 pointD(-fValue, fValue, 0.0f); //3

	vector3 pointE(fValue, -fValue, -0.001f); //1
	vector3 pointF(-fValue, -fValue, -0.001f); //0
	vector3 pointG(fValue, fValue, -0.001f); //2
	vector3 pointH(-fValue, fValue, -0.001f); //3

											  //F
	AddQuad(pointA, pointB, pointD, pointC);
	//Double sided
	AddQuad(pointE, pointF, pointG, pointH);

	CompileObject(a_v3Color);
}
void MyPrimitive::GenerateCube(float a_fSize, vector3 a_v3Color)
{
	if (a_fSize < 0.01f)
		a_fSize = 0.01f;

	Release();
	Init();

	float fValue = 0.5f * a_fSize;
	//3--2
	//|  |
	//0--1
	vector3 point0(-fValue, -fValue, fValue); //0
	vector3 point1(fValue, -fValue, fValue); //1
	vector3 point2(fValue, fValue, fValue); //2
	vector3 point3(-fValue, fValue, fValue); //3

	vector3 point4(-fValue, -fValue, -fValue); //4
	vector3 point5(fValue, -fValue, -fValue); //5
	vector3 point6(fValue, fValue, -fValue); //6
	vector3 point7(-fValue, fValue, -fValue); //7

											  //F
	AddQuad(point0, point1, point3, point2);

	//B
	AddQuad(point5, point4, point6, point7);

	//L
	AddQuad(point4, point0, point7, point3);

	//R
	AddQuad(point1, point5, point2, point6);

	//U
	AddQuad(point3, point2, point7, point6);

	//D
	AddQuad(point4, point5, point0, point1);

	CompileObject(a_v3Color);
}
void MyPrimitive::GenerateCone(float a_fRadius, float a_fHeight, int a_nSubdivisions, vector3 a_v3Color)
{
	if (a_nSubdivisions < 3)
		a_nSubdivisions = 3;
	if (a_nSubdivisions > 360)
		a_nSubdivisions = 360;

	Release();
	Init();

	//reference values
	float fValue = 0.5f * a_fHeight;
	vector3* base_points = new vector3[a_nSubdivisions];
	vector3 base(0, -fValue, 0);
	vector3 apex(0, fValue, 0);

	//base verteces
	for (int n = 0; n < a_nSubdivisions; n++) {
		base_points[n] = vector3(
			base.x + a_fRadius * cosf( n * ((2 * PI) / a_nSubdivisions)),
			base.y,
			base.z + a_fRadius * sinf( n * ((2 * PI) / a_nSubdivisions))
		);
	}

	//add sides
	for (int n = 0; n < a_nSubdivisions - 1; n++) {
		AddVertexPosition(apex);
		AddVertexPosition(base_points[n + 1]);
		AddVertexPosition(base_points[n]);
	}
	AddVertexPosition(apex);
	AddVertexPosition(base_points[0]);
	AddVertexPosition(base_points[a_nSubdivisions - 1]);

	//add base
	for (int n = 0; n < a_nSubdivisions - 1; n++) {
		AddVertexPosition(base);
		AddVertexPosition(base_points[n]);
		AddVertexPosition(base_points[n + 1]);
	}
	AddVertexPosition(base);
	AddVertexPosition(base_points[a_nSubdivisions - 1]);
	AddVertexPosition(base_points[0]);

	//cleanup
	delete[] base_points;
	base_points = nullptr;

	//Your code ends here
	CompileObject(a_v3Color);
}
void MyPrimitive::GenerateCylinder(float a_fRadius, float a_fHeight, int a_nSubdivisions, vector3 a_v3Color)
{
	if (a_nSubdivisions < 3)
		a_nSubdivisions = 3;
	if (a_nSubdivisions > 360)
		a_nSubdivisions = 360;

	Release();
	Init();

	//your code starts here

	//reference values
	float fValue = 0.5f * a_fHeight;
	vector3* base_points = new vector3[a_nSubdivisions];
	vector3 base(0, -fValue, 0);
	vector3* top_points = new vector3[a_nSubdivisions];
	vector3 top(0, fValue, 0);

	//base verteces
	for (int n = 0; n < a_nSubdivisions; n++) {
		base_points[n] = vector3(
			base.x + a_fRadius * cosf(n * ((2 * PI) / a_nSubdivisions)),
			base.y,
			base.z + a_fRadius * sinf(n * ((2 * PI) / a_nSubdivisions))
		);
	}

	//top verteces
	for (int n = 0; n < a_nSubdivisions; n++) {
		top_points[n] = vector3(
			top.x + a_fRadius * cosf(n * ((2 * PI) / a_nSubdivisions)),
			top.y,
			top.z + a_fRadius * sinf(n * ((2 * PI) / a_nSubdivisions))
		);
	}

	//add base
	for (int n = 0; n < a_nSubdivisions - 1; n++) {
		AddVertexPosition(base);
		AddVertexPosition(base_points[n]);
		AddVertexPosition(base_points[n + 1]);
	}
	AddVertexPosition(base);
	AddVertexPosition(base_points[a_nSubdivisions - 1]);
	AddVertexPosition(base_points[0]);

	//add top
	for (int n = 0; n < a_nSubdivisions - 1; n++) {
		AddVertexPosition(top);
		AddVertexPosition(top_points[n + 1]);
		AddVertexPosition(top_points[n]);
	}
	AddVertexPosition(top);
	AddVertexPosition(top_points[0]);
	AddVertexPosition(top_points[a_nSubdivisions - 1]);

	//add sides
	for (int n = 0; n < a_nSubdivisions - 1; n++) {
		AddQuad(top_points[n], top_points[n + 1], base_points[n], base_points[n + 1]);
	}
	AddQuad(top_points[a_nSubdivisions - 1], top_points[0], base_points[a_nSubdivisions - 1], base_points[0]);

	//cleanup
	delete[] base_points;
	base_points = nullptr;
	delete[] top_points;
	top_points = nullptr;

	//Your code ends here
	CompileObject(a_v3Color);
}
void MyPrimitive::GenerateTube(float a_fOuterRadius, float a_fInnerRadius, float a_fHeight, int a_nSubdivisions, vector3 a_v3Color)
{
	if (a_nSubdivisions < 3)
		a_nSubdivisions = 3;
	if (a_nSubdivisions > 360)
		a_nSubdivisions = 360;

	Release();
	Init();

	//Your code starts here

	//reference values
	float fValue = 0.5f * a_fHeight;
	vector3* base_inner_points = new vector3[a_nSubdivisions];
	vector3* base_outer_points = new vector3[a_nSubdivisions];
	vector3 base(0, -fValue, 0);
	vector3* top_inner_points = new vector3[a_nSubdivisions];
	vector3* top_outer_points = new vector3[a_nSubdivisions];
	vector3 top(0, fValue, 0);

	//base verteces
	for (int n = 0; n < a_nSubdivisions; n++) {
		base_inner_points[n] = vector3(
			base.x + a_fInnerRadius * cosf(n * ((2 * PI) / a_nSubdivisions)),
			base.y,
			base.z + a_fInnerRadius * sinf(n * ((2 * PI) / a_nSubdivisions))
		);
		base_outer_points[n] = vector3(
			base.x + a_fOuterRadius * cosf(n * ((2 * PI) / a_nSubdivisions)),
			base.y,
			base.z + a_fOuterRadius * sinf(n * ((2 * PI) / a_nSubdivisions))
		);
	}

	//top verteces
	for (int n = 0; n < a_nSubdivisions; n++) {
		top_inner_points[n] = vector3(
			top.x + a_fInnerRadius * cosf(n * ((2 * PI) / a_nSubdivisions)),
			top.y,
			top.z + a_fInnerRadius * sinf(n * ((2 * PI) / a_nSubdivisions))
		);
		top_outer_points[n] = vector3(
			top.x + a_fOuterRadius * cosf(n * ((2 * PI) / a_nSubdivisions)),
			top.y,
			top.z + a_fOuterRadius * sinf(n * ((2 * PI) / a_nSubdivisions))
		);
	}

	//add base
	for (int n = 0; n < a_nSubdivisions - 1; n++) {
		AddQuad(base_outer_points[n], base_outer_points[n + 1], base_inner_points[n], base_inner_points[n + 1]);
	}
	AddQuad(base_outer_points[a_nSubdivisions - 1], base_outer_points[0], base_inner_points[a_nSubdivisions - 1], base_inner_points[0]);

	//add top
	for (int n = 0; n < a_nSubdivisions - 1; n++) {
		AddQuad(top_inner_points[n], top_inner_points[n + 1], top_outer_points[n], top_outer_points[n + 1]);
	}
	AddQuad(top_inner_points[a_nSubdivisions - 1], top_inner_points[0], top_outer_points[a_nSubdivisions - 1], top_outer_points[0]);

	//add outer sides
	for (int n = 0; n < a_nSubdivisions - 1; n++) {
		AddQuad(top_outer_points[n], top_outer_points[n + 1], base_outer_points[n], base_outer_points[n + 1]);
	}
	AddQuad(top_outer_points[a_nSubdivisions - 1], top_outer_points[0], base_outer_points[a_nSubdivisions - 1], base_outer_points[0]);

	//add inner sides
	for (int n = 0; n < a_nSubdivisions - 1; n++) {
		AddQuad(base_inner_points[n], base_inner_points[n + 1], top_inner_points[n], top_inner_points[n + 1]);
	}
	AddQuad(base_inner_points[a_nSubdivisions - 1], base_inner_points[0], top_inner_points[a_nSubdivisions - 1], top_inner_points[0]);

	//cleanup
	delete[] base_inner_points;
	delete[] base_outer_points;
	base_inner_points = nullptr;
	base_outer_points = nullptr;
	delete[] top_inner_points;
	delete[] top_outer_points;
	top_inner_points = nullptr;
	top_outer_points = nullptr;

	//Your code ends here
	CompileObject(a_v3Color);
}
void MyPrimitive::GenerateTorus(float a_fOuterRadius, float a_fInnerRadius, int a_nSubdivisionsA, int a_nSubdivisionsB, vector3 a_v3Color)
{
	if (a_fOuterRadius <= a_fInnerRadius + 0.1f)
		return;

	if (a_nSubdivisionsA < 3)
		a_nSubdivisionsA = 3;
	if (a_nSubdivisionsA > 25)
		a_nSubdivisionsA = 25;

	if (a_nSubdivisionsB < 3)
		a_nSubdivisionsB = 3;
	if (a_nSubdivisionsB > 25)
		a_nSubdivisionsB = 25;

	Release();
	Init();

	//Your code starts here
	float fValue = 0.5f;
	//3--2
	//|  |
	//0--1
	vector3 point0(-fValue, -fValue, fValue); //0
	vector3 point1(fValue, -fValue, fValue); //1
	vector3 point2(fValue, fValue, fValue); //2
	vector3 point3(-fValue, fValue, fValue); //3

	AddQuad(point0, point1, point3, point2);

	//Your code ends here
	CompileObject(a_v3Color);
}
void MyPrimitive::GenerateSphere(float a_fRadius, int a_nSubdivisions, vector3 a_v3Color)
{
	//Sets minimum and maximum of subdivisions
	if (a_nSubdivisions < 1)
	{
		GenerateCube(a_fRadius * 2, a_v3Color);
		return;
	}
	if (a_nSubdivisions > 6)
		a_nSubdivisions = 6;

	Release();
	Init();

	//Your code starts here
	//reference values
	float fValue = a_fRadius;
	vector3 base(0, fValue, 0);
	vector3 top(0, -fValue, 0);
	vector3* points = new vector3[a_nSubdivisions * a_nSubdivisions];
	int base_points_i = a_nSubdivisions;
	int top_points_i = a_nSubdivisions * a_nSubdivisions;

	//verteces
	for (int r = 0; r < a_nSubdivisions; r++) {
		float height = a_fRadius * cosf(r * (PI / a_nSubdivisions));
		for (int n = 0; n < a_nSubdivisions; n++) {
			points[(r*a_nSubdivisions)+n] = vector3(
				a_fRadius * cosf(n * ((2 * PI) / a_nSubdivisions)) * sinf(r * ( PI / a_nSubdivisions)),
				height,
				a_fRadius * sinf(n * ((2 * PI) / a_nSubdivisions)) * sinf(r * ( PI / a_nSubdivisions))
			);
		}
	}

	//add base (actually top)
	for (int n = base_points_i - a_nSubdivisions; n < base_points_i - 1; n++) {
		AddVertexPosition(base);
		AddVertexPosition(points[n + 1]);
		AddVertexPosition(points[n]);
		
	}
	AddVertexPosition(base);
	AddVertexPosition(points[base_points_i - 1]);
	AddVertexPosition(points[base_points_i - a_nSubdivisions]);
	

	//add top (actually base)
	for (int n = top_points_i - a_nSubdivisions; n < top_points_i - 1; n++) {
		AddVertexPosition(top);
		AddVertexPosition(points[n]);
		AddVertexPosition(points[n + 1]);
	}
	AddVertexPosition(top);
	AddVertexPosition(points[top_points_i - 1]);
	AddVertexPosition(points[top_points_i - a_nSubdivisions]);
	
	//add sides
	for (int r = 1; r < a_nSubdivisions; r++) {
		for (int n = 0; n < a_nSubdivisions - 1; n++) {
			AddQuad(points[(r - 1) * a_nSubdivisions + n], points[(r - 1) * a_nSubdivisions + n + 1],
				points[r * a_nSubdivisions + n], points[r * a_nSubdivisions + n + 1]);
		}
		AddQuad(points[(r - 1) * a_nSubdivisions + a_nSubdivisions - 1], points[(r - 1) * a_nSubdivisions],
			points[r * a_nSubdivisions + a_nSubdivisions - 1], points[r * a_nSubdivisions]);
	}
	
	//cleanup
	delete[] points;
	points = nullptr;

	//Your code ends here
	CompileObject(a_v3Color);
}