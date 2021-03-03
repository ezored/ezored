ROOT_DIR=${PWD}

.DEFAULT_GOAL := help

# general
help:
	@echo "Type: make [rule]. Available options are:"
	@echo ""
	@echo "- help"
	@echo "- git-update-submodules"
	@echo "- clean-derived-data"	
	@echo "- pods-update"
	@echo "- remove-pods"
	@echo "- format"	
	@echo ""

git-update-submodules:
	git submodule update --recursive --remote

clean-derived-data:
	rm -rf ~/Library/Developer/Xcode/DerivedData

pods-update:
	rm -rf Pods
	rm -rf Podfile.lock
	rm -rf Sample.xcworkspace
	pod cache clean --all
	pod install --repo-update

remove-pods:
	rm -rf Pods
	rm -rf Podfile.lock
	rm -rf Sample.xcworkspace

format:
	swiftformat --swiftversion 5.0 Sample/
