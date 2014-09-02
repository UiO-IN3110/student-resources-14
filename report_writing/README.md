

## Installasjon på Mac / OS X

Dersom du skal bruke `latex_report_minted.tex` på OS X trenger du litt mer enn bare grunnleggende LaTeX.

1. Hvis du ikke har installert LaTeX, last ned og installer [BasicTeX.pkg](http://mirror.ctan.org/systems/mac/mactex/mactex-basic.pkg) fra [denne siden](https://tug.org/mactex/morepackages.html)
2. Kjør kommando: `sudo tlmgr install minted`
3. Kjør kommando: `sudo tlmgr install ifplatform`
4. Kjør kommando: `pip install pygments`
4. Du er klar til lage pdf: `pdflatex -shell-escape dinlatexfil.tex`