##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Release
ProjectName            :=P2Final
ConfigurationName      :=Release
WorkspacePath          :=/Users/blaine/Documents/C++
ProjectPath            :=/Users/blaine/Documents/C++/P2Final
IntermediateDirectory  :=./Release
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=Blaine Sieck
Date                   :=13/03/2019
CodeLitePath           :="/Users/blaine/Library/Application Support/codelite"
LinkerName             :=g++
SharedObjectLinkerName :=g++ -dynamiclib -fPIC
ObjectSuffix           :=.o
DependSuffix           :=.o.d
PreprocessSuffix       :=.o.i
DebugSwitch            :=-gstab
IncludeSwitch          :=-I
LibrarySwitch          :=-l
OutputSwitch           :=-o 
LibraryPathSwitch      :=-L
PreprocessorSwitch     :=-D
SourceSwitch           :=-c 
OutputFile             :=$(IntermediateDirectory)/$(ProjectName)
Preprocessors          :=$(PreprocessorSwitch)NDEBUG 
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E 
ObjectsFileList        :="P2Final.txt"
PCHCompileFlags        :=
MakeDirCommand         :=mkdir -p
LinkOptions            :=  
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch). 
IncludePCH             := 
RcIncludePath          := 
Libs                   := 
ArLibs                 :=  
LibPath                := $(LibraryPathSwitch). 

##
## Common variables
## AR, CXX, CC, AS, CXXFLAGS and CFLAGS can be overriden using an environment variables
##
AR       := ar rcus
CXX      := g++
CC       := gcc
CXXFLAGS :=  -O2 -std=c++11 $(Preprocessors)
CFLAGS   :=  -O2 -Wall $(Preprocessors)
ASFLAGS  := 
AS       := as


##
## User defined environment variables
##
CodeLiteDir:=/Applications/codelite.app/Contents/SharedSupport/
Objects0=$(IntermediateDirectory)/project2-main.cpp$(ObjectSuffix) $(IntermediateDirectory)/project2.cpp$(ObjectSuffix) 



Objects=$(Objects0) 

##
## Main Build Targets 
##
.PHONY: all clean PreBuild PrePreBuild PostBuild MakeIntermediateDirs
all: $(OutputFile)

$(OutputFile): $(IntermediateDirectory)/.d $(Objects) 
	@$(MakeDirCommand) $(@D)
	@echo "" > $(IntermediateDirectory)/.d
	@echo $(Objects0)  > $(ObjectsFileList)
	$(LinkerName) $(OutputSwitch)$(OutputFile) @$(ObjectsFileList) $(LibPath) $(Libs) $(LinkOptions)

MakeIntermediateDirs:
	@test -d ./Release || $(MakeDirCommand) ./Release


$(IntermediateDirectory)/.d:
	@test -d ./Release || $(MakeDirCommand) ./Release

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/project2-main.cpp$(ObjectSuffix): project2-main.cpp $(IntermediateDirectory)/project2-main.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/Users/blaine/Documents/C++/P2Final/project2-main.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/project2-main.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/project2-main.cpp$(DependSuffix): project2-main.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/project2-main.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/project2-main.cpp$(DependSuffix) -MM project2-main.cpp

$(IntermediateDirectory)/project2-main.cpp$(PreprocessSuffix): project2-main.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/project2-main.cpp$(PreprocessSuffix) project2-main.cpp

$(IntermediateDirectory)/project2.cpp$(ObjectSuffix): project2.cpp $(IntermediateDirectory)/project2.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/Users/blaine/Documents/C++/P2Final/project2.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/project2.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/project2.cpp$(DependSuffix): project2.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/project2.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/project2.cpp$(DependSuffix) -MM project2.cpp

$(IntermediateDirectory)/project2.cpp$(PreprocessSuffix): project2.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/project2.cpp$(PreprocessSuffix) project2.cpp


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) -r ./Release/


