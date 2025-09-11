# colors
GREEN = $(shell tput -Txterm setaf 2)
YELLOW = $(shell tput -Txterm setaf 3)
WHITE = $(shell tput -Txterm setaf 7)
RESET = $(shell tput -Txterm sgr0)
GRAY = $(shell tput -Txterm setaf 6)
TARGET_MAX_CHAR_NUM = 20

## Remove
remove:
	rm -rf pkg
	rm -rf target

## Build to web assembly.
build:
	wasm-pack build --target web --out-dir pkg --release

	wasm-opt -Oz --strip-debug --strip-producers --strip-dwarf pkg/crypt_bg.wasm -o pkg/crypt_bg.final.wasm

## Revert web assembly to c language.
revert:
	wasm-decompile pkg/crypt_bg.final.wasm -o pkg/crypt.c

## Revert web assembly to c language by using wasm2c.
wasm2c:
	wasm2c pkg/crypt_bg.final.wasm -o pkg/crypt1.c

## Revert web assembly to wat.
wat:
	wasm2wat pkg/crypt_bg.final.wasm -o pkg/crypt.wat

## Revert web assembly to wat by using wasm-dis.
dis:
	wasm-dis pkg/crypt_bg.final.wasm -o pkg/crypt.dis.wat

## Shows help. | Help
help:
	@echo ''
	@echo 'Usage:'
	@echo ''
	@echo '  ${YELLOW}make${RESET} ${GREEN}<target>${RESET}'
	@echo ''
	@echo 'Targets:'
	@awk '/^[a-zA-Z\-]+:/ { \
		helpMessage = match(lastLine, /^## (.*)/); \
		if (helpMessage) { \
				if (index(lastLine, "|") != 0) { \
				stage = substr(lastLine, index(lastLine, "|") + 1); \
				printf "\n ${GRAY}%s: \n\n", stage;  \
			} \
			helpCommand = substr($$1, 0, index($$1, ":")-1); \
			helpMessage = substr(lastLine, RSTART + 3, RLENGTH); \
			if (index(lastLine, "|") != 0) { \
				helpMessage = substr(helpMessage, 0, index(helpMessage, "|")-1); \
			} \
			printf "  ${YELLOW}%-$(TARGET_MAX_CHAR_NUM)s${RESET} ${GREEN}%s${RESET}\n", helpCommand, helpMessage; \
		} \
	} \
	{ lastLine = $$0 }' $(MAKEFILE_LIST)
	@echo ''
