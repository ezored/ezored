ROOT_DIR=${PWD}
.DEFAULT_GOAL := help

help:
	@echo "Type: make [rule]. Available options are:"
	@echo ""
	@echo "- help"
	@echo "- clean-derived-data"	
	@echo "- pods-update"
	@echo "- pods-remove"
	@echo "- pods-clear-cache"
	@echo "- format"	
	@echo ""

clean-derived-data:
	rm -rf ~/Library/Developer/Xcode/DerivedData

pods-update:
	rm -rf Pods
	rm -rf Podfile.lock
	rm -rf Sample.xcworkspace
	pod install --repo-update

pods-clear-cache:
	pod cache clean 'ezored' --all

pods-remove:
	rm -rf Pods
	rm -rf Podfile.lock
	rm -rf Sample.xcworkspace

format:
	swiftformat --swiftversion 5.0 Sample/
