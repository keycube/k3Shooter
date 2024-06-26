# Makefile generated by MakefileGenerator.cs
# *DO NOT EDIT*

UNREALROOTPATH = /home/linuxcat/UnrealEngine
GAMEPROJECTFILE =/home/linuxcat/k3Shooter/k3Shooter.uproject

TARGETS = \
	k3Shooter-Linux-DebugGame  \
	k3Shooter-Linux-Shipping  \
	k3Shooter \
	k3ShooterEditor-Linux-DebugGame  \
	k3ShooterEditor-Linux-Shipping  \
	k3ShooterEditor \
	UnrealEditor-Linux-DebugGame  \
	UnrealEditor-Linux-Shipping  \
	UnrealEditor \
	UnrealGame-Linux-DebugGame  \
	UnrealGame-Linux-Shipping  \
	UnrealGame\
	configure

BUILD = bash "$(UNREALROOTPATH)/Engine/Build/BatchFiles/Linux/Build.sh"
PROJECTBUILD = "$(UNREALROOTPATH)/Engine/Binaries/ThirdParty/DotNet/6.0.302/linux/dotnet" "$(UNREALROOTPATH)/Engine/Binaries/DotNET/UnrealBuildTool/UnrealBuildTool.dll"

all: StandardSet

RequiredTools: CrashReportClient-Linux-Shipping CrashReportClientEditor-Linux-Shipping ShaderCompileWorker UnrealLightmass EpicWebHelper-Linux-Shipping

StandardSet: RequiredTools UnrealFrontend k3ShooterEditor UnrealInsights

DebugSet: RequiredTools UnrealFrontend-Linux-Debug k3ShooterEditor-Linux-Debug


k3Shooter-Linux-DebugGame:
	 $(PROJECTBUILD) k3Shooter Linux DebugGame  -project="$(GAMEPROJECTFILE)" $(ARGS)

k3Shooter-Linux-Shipping:
	 $(PROJECTBUILD) k3Shooter Linux Shipping  -project="$(GAMEPROJECTFILE)" $(ARGS)

k3Shooter:
	 $(PROJECTBUILD) k3Shooter Linux Development  -project="$(GAMEPROJECTFILE)" $(ARGS)

k3ShooterEditor-Linux-DebugGame:
	 $(PROJECTBUILD) k3ShooterEditor Linux DebugGame  -project="$(GAMEPROJECTFILE)" $(ARGS)

k3ShooterEditor-Linux-Shipping:
	 $(PROJECTBUILD) k3ShooterEditor Linux Shipping  -project="$(GAMEPROJECTFILE)" $(ARGS)

k3ShooterEditor:
	 $(PROJECTBUILD) k3ShooterEditor Linux Development  -project="$(GAMEPROJECTFILE)" $(ARGS)

UnrealEditor-Linux-DebugGame:
	 $(BUILD) UnrealEditor Linux DebugGame  -project="$(GAMEPROJECTFILE)" $(ARGS)

UnrealEditor-Linux-Shipping:
	 $(BUILD) UnrealEditor Linux Shipping  -project="$(GAMEPROJECTFILE)" $(ARGS)

UnrealEditor:
	 $(BUILD) UnrealEditor Linux Development  -project="$(GAMEPROJECTFILE)" $(ARGS)

UnrealGame-Linux-DebugGame:
	 $(BUILD) UnrealGame Linux DebugGame  -project="$(GAMEPROJECTFILE)" $(ARGS)

UnrealGame-Linux-Shipping:
	 $(BUILD) UnrealGame Linux Shipping  -project="$(GAMEPROJECTFILE)" $(ARGS)

UnrealGame:
	 $(BUILD) UnrealGame Linux Development  -project="$(GAMEPROJECTFILE)" $(ARGS)

configure:
	xbuild /property:Configuration=Development /verbosity:quiet /nologo "$(UNREALROOTPATH)/Engine/Source/Programs/UnrealBuildTool/UnrealBuildTool.csproj"
	$(PROJECTBUILD) -projectfiles -project="\"$(GAMEPROJECTFILE)\"" -game -engine 

.PHONY: $(TARGETS)
