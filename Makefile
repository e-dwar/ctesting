
srcdir = src
objdir = build
tstdir = tests
exe = exec_tests

$(shell mkdir -p $(objdir))
$(shell mkdir -p $(objdir)/$(srcdir))
$(shell mkdir -p $(objdir)/$(tstdir))

exec_tests_deps = \
    $(objdir)/$(srcdir)/list.o \
    $(objdir)/$(srcdir)/test.o \
    $(objdir)/$(tstdir)/list_tests.o \
    $(objdir)/$(tstdir)/exec_tests.o

all: $(exe)

exec_tests: $(exec_tests_deps)
	gcc $(exec_tests_deps) -o $@

$(objdir)/$(srcdir)/%.o: $(srcdir)/%.c $(srcdir)/%.h
	gcc -c $< -o $@

$(objdir)/$(tstdir)/%.o: $(tstdir)/%.c $(tstdir)/%.h
	gcc -c $< -o $@

clean:
	rm -rf $(objdir) $(exe)
