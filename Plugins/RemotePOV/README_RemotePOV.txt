RemotePOV Plugin (UE5) — True Online Co-op Dual View
====================================================

Folder placement:
-----------------
Put this entire folder at:
  <YourProject>/Plugins/RemotePOV/

So you should have:
  <YourProject>/Plugins/RemotePOV/RemotePOV.uplugin
  <YourProject>/Plugins/RemotePOV/Source/RemotePOV/...


Build steps:
------------
1) Right-click your .uproject -> "Generate Visual Studio project files".
2) Open the solution and build "Development Editor", OR open the project in Unreal and let it build.
3) In Unreal: Edit -> Plugins -> ensure "RemotePOV" is enabled (Runtime). Restart if asked.


Integration (fast path):
------------------------
A) Use the provided base PlayerController:

   - In Project Settings -> Maps & Modes, set your GameMode's PlayerController Class to:
       RemotePOVPlayerControllerBase  (or make a BP child and use that)

   - This base PC will automatically ensure a camera state replicator exists on the server
     and will stream your local camera state to the server at ~30 Hz.

B) Show the other player's camera locally:

   In your PlayerController (Blueprint or code), after BeginPlay:
   - Call: FindOtherPlayersReplicator(self)  -> ARemoteCameraStateReplicator*
   - Call: SpawnPOVCaptureFor(self, TargetRep, OutCapture, 1280, 720)
   - Create a widget of class URemotePOVWidget, set CaptureActor = OutCapture, AddToViewport().
   - Optionally size/position for PiP or half-screen.

Play-in-Editor multiplayer test:
--------------------------------
- In the Play dropdown: Number of Players = 2, Net Mode = Play As Listen Server.
- Hit Play -> two windows open (Host + Client).
- Each window shows its own main gameplay PLUS a second view (the other player's camera),
  rendered locally via SceneCapture2D.

Performance tips:
-----------------
- Lower RenderTarget resolution (e.g., 960x540).
- In ARemotePOVCapture: set bCaptureEveryFrame=false and CaptureEveryNFrames=2 or 3.
- Heavy ShowFlags (SSR, AO) are disabled by default for the capture. Toggle back if needed.
- For larger worlds, ensure streaming and net relevancy consider BOTH players (see conversation notes).


Files included:
---------------
- RemotePOV.uplugin
- Source/RemotePOV/RemotePOV.Build.cs
- Public/NetCameraState.h
- Public/RemoteCameraStateReplicator.h
- Private/RemoteCameraStateReplicator.cpp
- Public/RemotePOVCapture.h
- Private/RemotePOVCapture.cpp
- Public/RemotePOVPlayerControllerBase.h
- Private/RemotePOVPlayerControllerBase.cpp
- Public/RemotePOVFunctionLibrary.h
- Private/RemotePOVFunctionLibrary.cpp
- Public/RemotePOVWidget.h
- Private/RemotePOVWidget.cpp
- Private/RemotePOV.cpp