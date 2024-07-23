LIBNAME = viewer3d_lib.a
CHECKFLAGS = $(shell pkg-config --cflags --libs check)
GCOVFLAGS = -fprofile-arcs -ftest-coverage
GLFLAGS = --coverage
FUNC_FILES_C = app/C_module/affine_transformations/*.c app/C_module/matrix_core/*.c app/C_module/wireframe_and_parser/*.c
FLAGS = gcc -Wall -Werror -Wextra --std=c11
EXCLUDE = --exclude "tests/*" --exclude "app/C_module/matrix_core/*"
QMAKE6_TRASH = .qmake.stash Makefile moc** *.o

all: install

install:
	cd app && qmake6 3DViewer_v1.0.pro && make
	make uninstall && mkdir out
	mv app/viewer3D out
	cd app && rm -rf $(QMAKE6_TRASH)
	make run

run:
	./out/viewer3D

uninstall:
	rm -rf out/* out

dist:
	tar -cf 3DViewer.tar app/images -C out .

build_library:
	ar rcs $(LIBNAME) *.o

viewer3d_lib.a:
	$(FLAGS) -c $(FUNC_FILES_C)
	make build_library
	rm -rf *.o

test: viewer3d_lib.a
	gcc tests/affine_transformations_move_test.c -L. $(LIBNAME) $(CHECKFLAGS) $(GLFLAGS) $(GCOVFLAGS) -o affine_transformations_move_test
	gcc tests/affine_transformations_scaling_test.c -L. $(LIBNAME) $(CHECKFLAGS) $(GLFLAGS) $(GCOVFLAGS) -o affine_transformations_scaling_test
	gcc tests/affine_transformations_rotation_test.c -L. $(LIBNAME)  $(CHECKFLAGS) $(GLFLAGS) $(GCOVFLAGS) -o affine_transformations_rotation_test
	gcc tests/obj_file_parser_test.c -L. $(LIBNAME) $(CHECKFLAGS) $(GLFLAGS) $(GCOVFLAGS) -o obj_file_parser_test
	make start_tests

start_tests:
	./affine_transformations_move_test
	./affine_transformations_scaling_test
	./affine_transformations_rotation_test
	./obj_file_parser_test

build_object_files_with_gcov:
	$(FLAGS) $(GCOVFLAGS) $(GLFLAGS) -c $(FUNC_FILES_C)


gcov_report: build_object_files_with_gcov build_library test
	gcov $(FUNC_FILES_C) 
	~/.local/bin/gcovr -r . $(EXCLUDE) --html --html-details -o s21_3dviewer.html

peer: 
	make gcov_report
	google-chrome s21_3dviewer.html

dvi:
	google-chrome doc/html/index.html

clean:
	cd app && rm -rf *.o Makefile moc** .qmake.stash viewer3D
	rm -rf *.a *.o *_test *.html *.css *.gif *.gcno *.gcda *.gcov 
	rm -rf *.jpeg *.bmp

rebuild: all