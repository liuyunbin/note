
farm.o:     file format elf64-x86-64


Disassembly of section .text:

0000000000000000 <start_farm>:
   0:	f3 0f 1e fa          	endbr64 
   4:	b8 01 00 00 00       	mov    $0x1,%eax
   9:	c3                   	retq   

000000000000000a <getval_142>:
   a:	f3 0f 1e fa          	endbr64 
   e:	b8 fb 78 90 90       	mov    $0x909078fb,%eax
  13:	c3                   	retq   

0000000000000014 <addval_273>:
  14:	f3 0f 1e fa          	endbr64 
  18:	8d 87 48 89 c7 c3    	lea    -0x3c3876b8(%rdi),%eax
  1e:	c3                   	retq   

000000000000001f <addval_219>:
  1f:	f3 0f 1e fa          	endbr64 
  23:	8d 87 51 73 58 90    	lea    -0x6fa78caf(%rdi),%eax
  29:	c3                   	retq   

000000000000002a <setval_237>:
  2a:	f3 0f 1e fa          	endbr64 
  2e:	c7 07 48 89 c7 c7    	movl   $0xc7c78948,(%rdi)
  34:	c3                   	retq   

0000000000000035 <setval_424>:
  35:	f3 0f 1e fa          	endbr64 
  39:	c7 07 54 c2 58 92    	movl   $0x9258c254,(%rdi)
  3f:	c3                   	retq   

0000000000000040 <setval_470>:
  40:	f3 0f 1e fa          	endbr64 
  44:	c7 07 63 48 8d c7    	movl   $0xc78d4863,(%rdi)
  4a:	c3                   	retq   

000000000000004b <setval_426>:
  4b:	f3 0f 1e fa          	endbr64 
  4f:	c7 07 48 89 c7 90    	movl   $0x90c78948,(%rdi)
  55:	c3                   	retq   

0000000000000056 <getval_280>:
  56:	f3 0f 1e fa          	endbr64 
  5a:	b8 29 58 90 c3       	mov    $0xc3905829,%eax
  5f:	c3                   	retq   

0000000000000060 <mid_farm>:
  60:	f3 0f 1e fa          	endbr64 
  64:	b8 01 00 00 00       	mov    $0x1,%eax
  69:	c3                   	retq   

000000000000006a <add_xy>:
  6a:	f3 0f 1e fa          	endbr64 
  6e:	48 8d 04 37          	lea    (%rdi,%rsi,1),%rax
  72:	c3                   	retq   

0000000000000073 <getval_481>:
  73:	f3 0f 1e fa          	endbr64 
  77:	b8 5c 89 c2 90       	mov    $0x90c2895c,%eax
  7c:	c3                   	retq   

000000000000007d <setval_296>:
  7d:	f3 0f 1e fa          	endbr64 
  81:	c7 07 99 d1 90 90    	movl   $0x9090d199,(%rdi)
  87:	c3                   	retq   

0000000000000088 <addval_113>:
  88:	f3 0f 1e fa          	endbr64 
  8c:	8d 87 89 ce 78 c9    	lea    -0x36873177(%rdi),%eax
  92:	c3                   	retq   

0000000000000093 <addval_490>:
  93:	f3 0f 1e fa          	endbr64 
  97:	8d 87 8d d1 20 db    	lea    -0x24df2e73(%rdi),%eax
  9d:	c3                   	retq   

000000000000009e <getval_226>:
  9e:	f3 0f 1e fa          	endbr64 
  a2:	b8 89 d1 48 c0       	mov    $0xc048d189,%eax
  a7:	c3                   	retq   

00000000000000a8 <setval_384>:
  a8:	f3 0f 1e fa          	endbr64 
  ac:	c7 07 81 d1 84 c0    	movl   $0xc084d181,(%rdi)
  b2:	c3                   	retq   

00000000000000b3 <addval_190>:
  b3:	f3 0f 1e fa          	endbr64 
  b7:	8d 87 41 48 89 e0    	lea    -0x1f76b7bf(%rdi),%eax
  bd:	c3                   	retq   

00000000000000be <setval_276>:
  be:	f3 0f 1e fa          	endbr64 
  c2:	c7 07 88 c2 08 c9    	movl   $0xc908c288,(%rdi)
  c8:	c3                   	retq   

00000000000000c9 <addval_436>:
  c9:	f3 0f 1e fa          	endbr64 
  cd:	8d 87 89 ce 90 90    	lea    -0x6f6f3177(%rdi),%eax
  d3:	c3                   	retq   

00000000000000d4 <getval_345>:
  d4:	f3 0f 1e fa          	endbr64 
  d8:	b8 48 89 e0 c1       	mov    $0xc1e08948,%eax
  dd:	c3                   	retq   

00000000000000de <addval_479>:
  de:	f3 0f 1e fa          	endbr64 
  e2:	8d 87 89 c2 00 c9    	lea    -0x36ff3d77(%rdi),%eax
  e8:	c3                   	retq   

00000000000000e9 <addval_187>:
  e9:	f3 0f 1e fa          	endbr64 
  ed:	8d 87 89 ce 38 c0    	lea    -0x3fc73177(%rdi),%eax
  f3:	c3                   	retq   

00000000000000f4 <setval_248>:
  f4:	f3 0f 1e fa          	endbr64 
  f8:	c7 07 81 ce 08 db    	movl   $0xdb08ce81,(%rdi)
  fe:	c3                   	retq   

00000000000000ff <getval_159>:
  ff:	f3 0f 1e fa          	endbr64 
 103:	b8 89 d1 38 c9       	mov    $0xc938d189,%eax
 108:	c3                   	retq   

0000000000000109 <addval_110>:
 109:	f3 0f 1e fa          	endbr64 
 10d:	8d 87 c8 89 e0 c3    	lea    -0x3c1f7638(%rdi),%eax
 113:	c3                   	retq   

0000000000000114 <addval_487>:
 114:	f3 0f 1e fa          	endbr64 
 118:	8d 87 89 c2 84 c0    	lea    -0x3f7b3d77(%rdi),%eax
 11e:	c3                   	retq   

000000000000011f <addval_201>:
 11f:	f3 0f 1e fa          	endbr64 
 123:	8d 87 48 89 e0 c7    	lea    -0x381f76b8(%rdi),%eax
 129:	c3                   	retq   

000000000000012a <getval_272>:
 12a:	f3 0f 1e fa          	endbr64 
 12e:	b8 99 d1 08 d2       	mov    $0xd208d199,%eax
 133:	c3                   	retq   

0000000000000134 <getval_155>:
 134:	f3 0f 1e fa          	endbr64 
 138:	b8 89 c2 c4 c9       	mov    $0xc9c4c289,%eax
 13d:	c3                   	retq   

000000000000013e <setval_299>:
 13e:	f3 0f 1e fa          	endbr64 
 142:	c7 07 48 89 e0 91    	movl   $0x91e08948,(%rdi)
 148:	c3                   	retq   

0000000000000149 <addval_404>:
 149:	f3 0f 1e fa          	endbr64 
 14d:	8d 87 89 ce 92 c3    	lea    -0x3c6d3177(%rdi),%eax
 153:	c3                   	retq   

0000000000000154 <getval_311>:
 154:	f3 0f 1e fa          	endbr64 
 158:	b8 89 d1 08 db       	mov    $0xdb08d189,%eax
 15d:	c3                   	retq   

000000000000015e <setval_167>:
 15e:	f3 0f 1e fa          	endbr64 
 162:	c7 07 89 d1 91 c3    	movl   $0xc391d189,(%rdi)
 168:	c3                   	retq   

0000000000000169 <setval_328>:
 169:	f3 0f 1e fa          	endbr64 
 16d:	c7 07 81 c2 38 d2    	movl   $0xd238c281,(%rdi)
 173:	c3                   	retq   

0000000000000174 <setval_450>:
 174:	f3 0f 1e fa          	endbr64 
 178:	c7 07 09 ce 08 c9    	movl   $0xc908ce09,(%rdi)
 17e:	c3                   	retq   

000000000000017f <addval_358>:
 17f:	f3 0f 1e fa          	endbr64 
 183:	8d 87 08 89 e0 90    	lea    -0x6f1f76f8(%rdi),%eax
 189:	c3                   	retq   

000000000000018a <addval_124>:
 18a:	f3 0f 1e fa          	endbr64 
 18e:	8d 87 89 c2 c7 3c    	lea    0x3cc7c289(%rdi),%eax
 194:	c3                   	retq   

0000000000000195 <getval_169>:
 195:	f3 0f 1e fa          	endbr64 
 199:	b8 88 ce 20 c0       	mov    $0xc020ce88,%eax
 19e:	c3                   	retq   

000000000000019f <setval_181>:
 19f:	f3 0f 1e fa          	endbr64 
 1a3:	c7 07 48 89 e0 c2    	movl   $0xc2e08948,(%rdi)
 1a9:	c3                   	retq   

00000000000001aa <addval_184>:
 1aa:	f3 0f 1e fa          	endbr64 
 1ae:	8d 87 89 c2 60 d2    	lea    -0x2d9f3d77(%rdi),%eax
 1b4:	c3                   	retq   

00000000000001b5 <getval_472>:
 1b5:	f3 0f 1e fa          	endbr64 
 1b9:	b8 8d ce 20 d2       	mov    $0xd220ce8d,%eax
 1be:	c3                   	retq   

00000000000001bf <setval_350>:
 1bf:	f3 0f 1e fa          	endbr64 
 1c3:	c7 07 48 89 e0 90    	movl   $0x90e08948,(%rdi)
 1c9:	c3                   	retq   

00000000000001ca <end_farm>:
 1ca:	f3 0f 1e fa          	endbr64 
 1ce:	b8 01 00 00 00       	mov    $0x1,%eax
 1d3:	c3                   	retq   
