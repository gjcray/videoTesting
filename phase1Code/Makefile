objects = main.o parse.o sockclnt.o videocapture.o y2b.o scale_block.o char_block.o matching.o

test: $(objects)
	g++ -g -o test $(objects)

.PHONY: clean cleandata

clean:
	rm test $(objects)

cleandata:
	rm ../data/orig_feature/* ../data/test_feature/* ../data/orig_snapshots/* ../data/test_snapshots/* ../data/result

