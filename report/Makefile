.PHONY: all
all: report.pdf

report.pdf: report.bbl 	\
			report.tex 	\
			sections/title-page.tex \
			sections/introduction.tex \
			sections/polynomial-mult.tex \
			sections/fft.tex \
			sections/a-plus-b.tex \
			sections/problem-993e.tex
	pdflatex report.tex

report.bbl: report.bib 
	pdflatex report.tex
	bibtex report
	pdflatex report.tex
