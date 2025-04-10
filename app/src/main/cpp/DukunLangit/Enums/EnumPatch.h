#pragma once

#define PATCH_ENUM \
X(DefaultShout) \
X(UnlockCloset) \
X(UnlockCloset2) \
X(UnlockCloset3) \
X(HDR) \
X(TrueCapeless) \
X(CrystalTumor) \
X(FullEnergy) \
X(FullEnergy2) \
X(DyingKid) \
X(AntiKrill) \
X(AntiKrill2) \
X(iOSHeadphones) \
X(RevealStranger) \
X(ScooterMode) \
X(BabyCrawl) \
X(BrokenNeck) \
X(RemoveBarriers) \
X(BurnPlants) \
X(BurnSpirits) \
X(BurnDyePlants) \
X(RemoveWindwalls) \
X(BurnCandles) \
X(OfflineMode) \
X(FastHome) \
X(InfiniteFireworks) \
X(InstantSeason) \
X(FastFlap) \
X(FastFlap2) \
X(UnlockEmotes) \
X(WaxAbsorb) \
X(DyeAbsorb) \
X(WideAngle) \
X(FreeZoom) \
X(RemoveClouds) \
X(GrassHeight) \
X(GrassScale) \
X(ZeroGravity) \
X(AvatarGlow) \
X(RunningSpeed) \
X(WingPower) \
X(JumpPower) \
X(DivingSpeed) \
X(Bleed) \
X(LightAll) \
X(ShowSpirits) \
X(RemovePortals) \
X(CleanUI) \
X(XRayVision) \
X(SeeThroughWater) \
X(SeeThrough1) \
X(SeeThrough2) \
X(SeeThrough3) \
X(SeeThrough4) \
X(FriendshipNodes) \
X(SkipCutscenes) \
X(ShowMapShrines) \
X(ShowWingedLights) \
X(HelplessCrabs) \
X(FreezeKrills) \
X(BirthdayKrills) \
X(AllergicKrills) \
X(HideAvatars) \
X(InvisibleCape) \
X(FakeAFK) \
X(FullOxygen) \
X(GameSpeed) \
X(CameraYaw) \
X(CameraPitch) \
X(CameraRoll) \
X(CameraDistance) \
X(CameraFreeze) \
X(CameraFreeze2) \
X(CameraFreeze3) \
X(WingCount) \
X(CandleCount) \
X(HeartCount) \
X(SeasonCandleCount) \
X(AscendedCandleCount) \
X(SeasonPackCount) \
X(SeasonHeartCount) \
X(SoulOfDukuns) \
X(FullBlue) \
X(AvatarHeight) \
X(AvatarScale) \
X(Spark) \
X(Invisible) \
X(Invisible2) \
X(AFKState) \
X(AFKState2) \
X(Count)

enum class PatchID {
#define X(name) name,
    PATCH_ENUM
#undef X
};