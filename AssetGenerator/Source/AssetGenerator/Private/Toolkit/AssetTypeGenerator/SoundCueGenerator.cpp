#include "Toolkit/AssetTypeGenerator/SoundCueGenerator.h"

#include "Framework/MultiBox/MultiBoxBuilder.h"
#include "EdGraph/EdGraphNode.h"
#include "Modules/ModuleManager.h"
#include "SoundCueGraph/SoundCueGraphNode.h"
#include "SoundCueGraph/SoundCueGraphNode_Root.h"
#include "Sound/SoundWave.h"
#include "Sound/SoundCue.h"
#include "ScopedTransaction.h"
#include "GraphEditor.h"
#include "EdGraphUtilities.h"
#include "SNodePanel.h"
#include "Editor.h"
#include "PropertyEditorModule.h"
#include "IDetailsView.h"
#include "Widgets/Docking/SDockTab.h"

#include "Dom/JsonObject.h"

UClass* USoundCueGenerator::GetAssetObjectClass()  const {
	return USoundCue::StaticClass();
}

FTopLevelAssetPath USoundCueGenerator::GetAssetClass() {
	return FTopLevelAssetPath(USoundCue::StaticClass());
}

void USoundCueGenerator::CreateAssetPackage() {
	UPackage* NewPackage = CreatePackage(*GetPackageName().ToString());
	USoundCue* SoundCue = NewObject<USoundCue>(NewPackage, GetAssetName(), RF_Public | RF_Standalone);
	SetPackageAndAsset(NewPackage, SoundCue);

	SoundCue->GetGraph()->Modify();
	SoundCue->Modify();

	const FString TextToImport = GetAssetData()->GetStringField(TEXT("SoundCueGraph")).ReplaceEscapedCharWithChar();
	
	// Import the nodes
	TSet<UEdGraphNode*> PastedNodes;
	FEdGraphUtilities::ImportNodesFromText(SoundCue->GetGraph(), TextToImport, /*out*/ PastedNodes);



	for (TSet<UEdGraphNode*>::TIterator It(PastedNodes); It; ++It)
	{
		UEdGraphNode* Node = *It;

		if (USoundCueGraphNode* SoundGraphNode = Cast<USoundCueGraphNode>(Node))
		{
			SoundCue->AllNodes.Add(SoundGraphNode->SoundNode);
		}

		if (Node->NodePosX == 0 && Node->NodePosY == 0) {
			for (UEdGraphNode* node : SoundCue->GetGraph()->Nodes)
			{
				if (USoundCueGraphNode_Root* root = Cast<USoundCueGraphNode_Root>(node)) {
					Node->FindPin(TEXT("Output"), EGPD_Output)->MakeLinkTo(root->Pins[0]);
				}
			}
			
		}
		Node->NodePosX = Node->NodePosX - 300;
		Node->SnapToGrid(SNodePanel::GetSnapGridSize());

		// Give new node a different Guid from the old one
		Node->CreateNewGuid();
	}

	// Force new pasted SoundNodes to have same connections as graph nodes
	SoundCue->CompileSoundNodesFromGraphNodes();

	// Update UI
	//SoundCueGraphEditor->NotifyGraphChanged();

	SoundCue->PostEditChange();
	SoundCue->MarkPackageDirty();


	PopulateSimpleAssetWithData(SoundCue);
}
