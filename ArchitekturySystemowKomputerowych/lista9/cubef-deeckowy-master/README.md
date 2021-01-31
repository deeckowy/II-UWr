Podnoszenie do sześcianu z zaokrąglaniem
===

W pliku `cubef.s` zaprogramuj w asemblerze `x86-64` procedurę o sygnaturze
`uint32_t cubef(uint32_t)`. Jej zadaniem jest podnieść do sześcianu liczbę
zmiennopozycyjną typu `float`, której reprezentację binarną umieszczono w
32-bitowym słowie typu `uint32_t`. Wynik należy zaokrąglić do najbliższej parzystej.
Zakładamy, że parametr procedury będzie taki, że wynik nigdy nie będzie 
niezerową liczbą zdenormalizowaną ani nie przyjmie wartości NaN.

<sub>**UWAGA!** Można używać tylko i wyłącznie instrukcji
całkowitoliczbowych!</sub>
