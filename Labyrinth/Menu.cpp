#include "Menu.h"

const BYTE minvalue = 0;
const BYTE maxchance = 100;
const BYTE maxtime = 10;

// Global vars
BYTE* pChance = NULL;
BYTE* pTime = NULL;
bool bDrawMenu = false;

void PaddedText(const char* text, float padx, float pady)
{
	ImVec2 sz = ImGui::CalcTextSize(text);
	ImVec2 cursor = ImGui::GetCursorPos();
	ImGui::InvisibleButton("##padded-text", sz + ImVec2(padx * 2, pady * 2));    // ImVec2 operators require imgui_internal.h include and -DIMGUI_DEFINE_MATH_OPERATORS=1
	ImVec2 final_cursor_pos = ImGui::GetCursorPos();
	ImGui::SetCursorPos(cursor + ImVec2(padx, pady));
	ImGui::Text(text);
	ImGui::SetCursorPos(final_cursor_pos);
}

void DrawMenu(Labyrinth* graph)
{
	ImGui_ImplWin32_NewFrame();
	ImGui_ImplDX9_NewFrame();
	ImGui::NewFrame();
	ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_Once);
	ImGui::SetNextWindowSize(ImVec2(300, 400), ImGuiCond_Once);
	ImGui::Begin("Graph", &bDrawMenu, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);
	ImGui::Columns(3);
	ImGui::SetColumnOffset(1, 100);
	ImGui::Text("Edge");
	for (BYTE i = 0; i < graph->GetVerticesCount(); i++)
	{
		for (BYTE j = 0; j < graph->GetVerticesCount(); j++)
		{
			if (graph->adjMat[i][j])
			{
				char szEdge[20];
				sprintf_s(szEdge, "Edge %d -> %d", i, j);
				PaddedText(szEdge, 0, 3);
			}
				
		}
	}
	ImGui::NextColumn();
	ImGui::Text("Time");
	for (BYTE i = 0; i < graph->GetVerticesCount(); i++)
	{
		for (BYTE j = 0; j < graph->GetVerticesCount(); j++)
		{
			if (graph->adjMat[i][j])
			{
				char id[30] = "S.##time";
				char num[15];
				sprintf_s(num, "%d%d", i, j);
				strcat_s(id, num);
				ImGui::DragScalar(id, ImGuiDataType_U8, graph->time.GetP(EDGE{ i, j }), 0.1, &minvalue, &maxtime, (const char*)0, ImGuiSliderFlags_AlwaysClamp);
			}			
		}
	}
	ImGui::NextColumn();
	ImGui::Text("Chance");
	for (BYTE i = 0; i < graph->GetVerticesCount(); i++)
	{
		for (BYTE j = 0; j < graph->GetVerticesCount(); j++)
		{
			if (graph->adjMat[i][j])
			{
				char id[30] = "%##chance";
				char num[15];
				sprintf_s(num, "%d%d", i, j);
				strcat_s(id, num);
				ImGui::DragScalar(id, ImGuiDataType_U8, graph->traps.GetP(EDGE{ i, j }), 0.3, &minvalue, &maxchance, (const char*)0, ImGuiSliderFlags_AlwaysClamp);
			}
				
		}
	}

	ImGui::End();
	ImGui::Render();
	ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
}