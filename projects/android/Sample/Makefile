.DEFAULT_GOAL := help

help:
	@echo "Type: make [rule]. Available options are:"
	@echo ""
	@echo "- help"
	@echo "- remove-trash"
	@echo "- format"
	@echo ""

remove-trash:
	find . -name ".DS_Store" -depth -exec rm -rf {} \;
	find . -name "Thumbs.db" -depth -exec rm -rf {} \;
	find . -name ".idea" -depth -exec rm -rf {} \;
	find . -name "*.iml" -depth -exec rm -rf {} \;

format:
	ktlint -F "app/**/*.kt"
