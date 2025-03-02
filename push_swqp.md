# Push_swap

## Because Swap_push isn’t as natural

_Summary:
This project will make you sort data on a stack, with a limited set of instructions, using the lowest possible number of actions. To succeed you’ll have to manipulate various types of algorithms and choose the most appropriate solution (out of many) for an optimized data sorting._

```
Version: 7
```

## Contents

- I Foreword
- II Introduction
- III Objectives
- IV Common Instructions
- V Mandatory part
   - V.1 The rules
   - V.2 Example
   - V.3 The "push_swap" program
- VI Bonus part
   - VI.1 The "checker" program
- VII Submission and peer-evaluation

_概要
このプロジェクトでは、限られた命令セットで、可能な限り少ないアクション数で、スタック上のデータをソートさせる。成功させるためには、様々な種類のアルゴリズムを操作し、最適化されたデータ・ソートのために（多くの中から）最も適切な解決策を選択しなければならない。

```
バージョン: 7
```

## 目次

- I 序文
- II はじめに
- III 目的
- IV 共通の指示
- V 必須部分
   - V.1 規則
   - V.2 例
   - V.3 「push_swap 」プログラム
- VI ボーナス・パート
   - VI.1 「チェッカー」プログラム
- VII 投稿と相互評価


# Chapter I

# Foreword

#### • C

```
#include <stdio.h>
int main(void)
{
printf("hello, world\n");
return 0;
}
```
#### • ASM

```
cseg segment
assume cs:cseg, ds:cseg
org 100h
main proc
jmp debut
mess db'Hello world!$'
debut:
mov dx, offset mess
mov ah, 9
int 21h
ret
main endp
cseg ends
end main
```
#### • LOLCODE

```
HAI
CAN HAS STDIO?
VISIBLE "HELLO WORLD!"
KTHXBYE
```
#### • PHP

```
<?php
echo "Hello world!";
?>
```
- BrainFuck ++++++++++[>+++++++>++++++++++>+++>+<<<<-] >++.>+.+++++++..+++.>++. <<+++++++++++++++.>.+++.------.--------.>+.>.


Push_swap Because Swap_push isn’t as natural

#### • C#

```
using System;
public class HelloWorld {
public static void Main () {
Console.WriteLine("Hello world!");
}
}
```
#### • HTML

```
<!DOCTYPE html>
<html>
<head>
<meta charset="utf-8">
<title>Hello world !</title>
</head>
<body>
<p>Hello World !</p>
</body>
</html>
```
#### • YASL

```
"Hello world!"
print
```
- OCaml let main () =    print_endline "Hello world !" let _ = main ()


# Chapter II

# Introduction

The **Push swap** project is a very simple and a highly straightforward algorithm project: data must be sorted.

You have at your disposal a set of integer values, 2 stacks, and a set of instructions to manipulate both stacks.

Your goal? Write a program in C calledpush_swap which calculates and displays on the standard output the smallest program, made of _Push swap language_ instructions, that sorts the integers received as arguments.

```
Easy?
```
```
We’ll see...
```

Push swap**プロジェクトは非常に単純で、非常にわかりやすいアルゴリズム・プロジェクトである。

データをソートしなければならない。自由に使えるのは、整数値のセット、2つのスタック、両方のスタックを操作するための命令セットである。

あなたの目標は？引数として受け取った整数をソートする、_Push swap language_ 命令で作られた最小のプログラムを計算し、標準出力に表示するpush_swapというプログラムをCで書きなさい。

```簡単か？
```
```そうだな...```

# Chapter III

# Objectives

Writing a sorting algorithm is always a very important step in a developer’s journey. It is often the first encounter with the concept of complexity.

Sorting algorithms and their complexity are part of the classic questions discussed during job interviews. It’s probably a good time to look at these concepts since you’ll have to face them at some point.

The learning objectives of this project are rigor, use ofC, and use of basic algorithms. Especially focusing on their complexity.

Sorting values is simple. To sort them the fastest way possible is less simple. Especially because from one integers configuration to another, the most efficient sorting solution can differ.



ソート・アルゴリズムを書くことは、開発者にとって常に非常に重要なステップである。多くの場合、複雑さの概念との最初の出会いでもある。

ソート・アルゴリズムとその複雑性は、就職面接の際に議論される典型的な質問の一部である。いずれは直面することになるだろうから、これらの概念に目を向けるのは良い機会だろう。

このプロジェクトの学習目標は、厳密性、Cの使用、基本的なアルゴリズムの使用である。特にその複雑さに焦点を当てる。

値の並べ替えは簡単だ。可能な限り最速の方法でソートすることは、それほど単純ではない。特に、整数の構成によって、最も効率的なソート方法が異なることがあるからだ。

# Chapter IV

# Common Instructions

- Your project must be written in C.
- Your project must be written in accordance with the Norm. If you have bonus files/functions, they are included in the norm check and you will receive a 0 if there is a norm error inside.
- Your functions should not quit unexpectedly (segmentation fault, bus error, double free, etc) apart from undefined behaviors. If this happens, your project will be considered non functional and will receive a 0 during the evaluation.
- All heap allocated memory space must be properly freed when necessary. No leaks will be tolerated.
- If the subject requires it, you must submit a Makefilewhich will compile your source files to the required output with the flags-Wall,-Wextraand-Werror, use cc, and your Makefile must not relink.
- YourMakefilemust at least contain the rules$(NAME),all,clean,fcleanand re.
- To turn in bonuses to your project, you must include a rulebonusto your Makefile, which will add all the various headers, librairies or functions that are forbidden on the main part of the project. Bonuses must be in a different file_bonus.{c/h}if the subject does not specify anything else. Mandatory and bonus part evaluation is done separately.
- If your project allows you to use your libft, you must copy its sources and its associatedMakefilein alibftfolder with its associated Makefile. Your project’s Makefilemust compile the library by using itsMakefile, then compile the project.
- We encourage you to create test programs for your project even though this work **won’t have to be submitted and won’t be graded**. It will give you a chance to easily test your work and your peers’ work. You will find those tests especially useful during your defence. Indeed, during defence, you are free to use your tests and/or the tests of the peer you are evaluating.
- Submit your work to your assigned git repository. Only the work in the git reposi- tory will be graded. If Deepthought is assigned to grade your work, it will be done


Push_swap Because Swap_push isn’t as natural

```
after your peer-evaluations. If an error happens in any section of your work during Deepthought’s grading, the evaluation will stop.
```

- あなたのプロジェクトはC言語で書かれていなければなりません。
- あなたのプロジェクトは規範に従って書かれていなければなりません。ボーナスファイル/関数がある場合、それらは規範チェックに含まれ、内部に規範エラーがある場合は0が返されます。
- 関数は、未定義の動作とは別に、予期せぬ終了（セグメンテーションフォールト、バスエラー、ダブルフリーなど）をしてはいけません。このような場合、プロジェクトは非機能とみなされ、評価中に0が返されます。
- ヒープに割り当てられたメモリ空間は、必要なときに適切に解放しなければなりません。リークは許されません。
- また、Makefileは再リンクしてはいけません。
- Makefileには少なくとも$(NAME),all,clean,fclean,reのルールが含まれていなければならない。- プロジェクトにボーナスを追加するには、Makefileにrulebonustを含める必要があります。このrulebonustは、プロジェクトのメイン部分で禁止されているさまざまなヘッダー、ライブラリ、関数をすべて追加します。ボーナスは、対象が他に何も指定しない場合は、別のファイル_bonus.{c/h}に記述する必要があります。必須パートとボーナスパートの評価は別々に行われます。
- プロジェクトで libft を使用する場合は、そのソースと関連する Makefile を alibft フォルダにコピーしてください。プロジェクトのMakefileは、そのMakefileを使用してライブラリをコンパイルしてから、プロジェクトをコンパイルする必要があります。
- この作業は**提出する必要はなく、採点もされません**が、プロジェクトのテストプログラムを作成することをお勧めします。自分の作品や仲間の作品を簡単にテストすることができます。これらのテストは、特にディフェンスの際に役立ちます。実際、ディフェンスの際には、あなたが作成したテストおよび/またはあなたが評価する仲間のテストを自由に使用することができます。
- 自分の作品を指定された git リポジトリに提出してください。git リポジトリにある作品のみが採点されます。Deepthought があなたの作品の採点を担当する場合、採点は以下のように行われます。


Push_swap Swap_push は自然ではないからです。

```
は自然ではないからです。Deepthoughtの採点中に作品のいずれかのセクションでエラーが発生した場合、評価は中断されます。
```

# Chapter V

# Mandatory part

### V.1 The rules

- You have 2 stacks namedaandb.
- At the beginning:

```
◦ The stack A contains a random amount of negative and/or positive numbers which cannot be duplicated.
◦ The stack B is empty.
```
- The goal is to sort in ascending order numbers into stack A. To do so you have the following operations at your disposal:

```
sa (swap a): Swap the first 2 elements at the top of stack A.
Do nothing if there is only one or no elements.
sb (swap b): Swap the first 2 elements at the top of stack B.
Do nothing if there is only one or no elements.
ss :sa and sb at the same time.
pa (push a): Take the first element at the top of B and put it at the top of A.
Do nothing ifbis empty.
pb (push b): Take the first element at the top of A and put it at the top of B.
Do nothing ifais empty.
ra (rotate a): Shift up all elements of stack A by 1.
The first element becomes the last one.
rb (rotate b): Shift up all elements of stack B by 1.
The first element becomes the last one.
rr : ra and rb at the same time.
rra (reverse rotate a): Shift down all elements of stack A by 1.
The last element becomes the first one.
rrb (reverse rotate b): Shift down all elements of stack B by 1.
The last element becomes the first one.
rrr :rra and rrb at the same time.
```


- あなたはa、bという2つのスタックを持っている。
- 最初に

```
スタックAには、複製できない負の数と正の数がランダムに含まれている。
スタックBは空である。
```
- 目標はスタック A に数字を昇順に並べ替えることである：

```
sa (swap a)： スタックAの先頭の2つの要素を入れ替える。
要素が1つしかない場合や要素がない場合は何もしない。
sb (swap b)： スタックBの先頭の2つの要素を入れ替えます。
要素が 1 つしかないか、ない場合は何もしない。
ss :sa と sb を同時に実行する。
pa (push a)： Bの先頭の要素を取り出し、Aの先頭に置く。
Bが空の場合は何もしない。
pb (push b)： pb(bを押す): Aの先頭の要素を取り、Bの先頭に置く。
空なら何もしない。
ra (rotate a)： スタック A のすべての要素を 1 ずらす。
最初の要素が最後の要素になる。
rb (rotate b)： スタック B のすべての要素を 1 ずらす。
最初の要素が最後の要素になる。
rr : ra と rb を同時に行う。
rra (reverse rotate a)： スタック A のすべての要素を 1 だけシフトダウンする。
最後の要素が最初の要素になる。
rrb (reverse rotate b)： スタック B のすべての要素を 1 だけシフトダウンする。
最後の要素が最初の要素になる。
rrr :rra と rrb を同時に行う。
```

Push_swap Because Swap_push isn’t as natural

### V.2 Example

To illustrate the effect of some of these instructions, let’s sort a random list of integers.
In this example, we’ll consider that both stacks grow from the right.

これらの命令の効果を説明するために、整数のランダムなリストをソートしてみよう。
この例では、どちらのスタックも右から大きくなると考える。

----------------------------------------------------------------------------------------------------------
Init a and b:
2
1
3
6
5
8

_ _
a b
----------------------------------------------------------------------------------------------------------
Exec sa:
1
2
3
6
5
8

_ _
a b
----------------------------------------------------------------------------------------------------------
Exec pb pb pb:
6 3
5 2
8 1
_ _
a b
----------------------------------------------------------------------------------------------------------
Exec ra rb (equiv. to rr):
5 2
8 1
6 3
_ _
a b
----------------------------------------------------------------------------------------------------------
Exec rra rrb (equiv. to rrr):
6 3
5 2
8 1
_ _
a b
----------------------------------------------------------------------------------------------------------
Exec sa:
5 3
6 2
8 1
_ _
a b
----------------------------------------------------------------------------------------------------------
Exec pa pa pa:
1 
2
3
5
6
8

_ _
a b
----------------------------------------------------------------------------------------------------------

```
Integers fromaget sorted in 12 instructions. Can you do better?
```

Push_swap Because Swap_push isn’t as natural

```
整数を12命令でソート。もっとうまくできるかい？
```

Push_swap Swap_pushが自然じゃないから。

### V.3 The "push_swap" program

```
Program name push_swap
Turn in files Makefile, *.h, *.c
Makefile NAME, all, clean, fclean, re
Arguments stack A : A list of integers
External functs.
```
- read, write, malloc, free, exit
- ft_printf and any equivalent YOU coded

```
Libft authorized Yes
Description Sort stacks
```
```
Your project must comply with the following rules:
```
- You have to turn in aMakefilewhich will compile your source files. It must not relink.
- Global variables are forbidden.
- You have to write a program namedpush_swapthat takes as an argument the stack A formatted as a list of integers. The first argument should be at the top of the stack (be careful about the order).
- The program must display the smallest list of instructions possible to sort the stack A , the smallest number being at the top.
- Instructions must be separated by a ’\n’ and nothing else.
- The goal is to sort the stack with the lowest possible number of operations. During the evaluation process, the number of instructions found by your program will be compared against a limit: the maximum number of operations tolerated. If your program either displays a longer list or if the numbers aren’t sorted properly, your grade will be 0.
- If no parameters are specified, the program must not display anything and give the prompt back.
- In case of error, it must display"Error"followed by a ’\n’ on the standard error. Errors include for example: some arguments aren’t integers, some arguments are bigger than an integer and/or there are duplicates.

```
プログラム名 push_swap
ファイル名 Makefile, *.h, *.c
Makefile NAME, all, clean, fclean, re
引数 stack A ： 整数のリスト
外部関数
```
- read、write、malloc、free、exit
- ft_printf およびそれに相当する YOU コード化された関数

```
Libft 公認
説明 スタックの並べ替え
```
```
プロジェクトは以下の規則に従わなければならない：
```
- ソースファイルをコンパイルするMakefileを提出しなければならない。再リンクしてはならない。
- グローバル変数は禁止されています。
- push_swapというプログラムを書かなければなりません。これはスタックを引数として取り、整数のリストとしてフォーマットします。最初の引数はスタックの先頭でなければならない（順番に注意）。
- プログラムはスタック a をソートするために可能な限り小さな命令リストを表示しなければならない。
- 命令は「'」で区切らなければならず、それ以外には何も入れてはならない。
- 目標は、可能な限り少ない操作回数でスタックをソートすることである。評価プロセス中、あなたのプログラムが見つけた命令の数は、許容される操作の最大数という制限と比較されます。あなたのプログラムがより長いリストを表示するか、数字が適切にソートされない場合、あなたの成績は 0 となります。
- パラメータが指定されていない場合、プログラムは何も表示せず、プロンプトを返さなければなりません。
- エラーの場合、標準エラーに 「Error 」の後に' \n'を表示しなければなりません。エラーとは例えば、引数が整数でない、引数が整数より大きい、重複している、などです。


Push_swap Because Swap_push isn’t as natural

$>./push_swap 2 1 3 6 5 8
sa
pb
pb
pb
sa
pa
pa
pa
$>./push_swap 0 one 2 3
Error
$>

During the evaluation process, a binary will be provided in order to properly check your program.
評価プロセスでは、プログラムを適切にチェックするためにバイナリが提供されます。

```
It will work as follows:
```
$>ARG="4 67 3 87 23"; ./push_swap $ARG | wc -l
6
$>ARG="4 67 3 87 23"; ./push_swap $ARG | ./checker_OS $ARG
OK
$>

If the programchecker_OSdisplays"KO", it means that yourpush_swapcame up with a list of instructions that doesn’t sort the numbers.

```
The checker_OS program is available in the resources of the project in the intranet. You can find a description of how it works in the Bonus Part of this document.
```

もしprogramchecker_OSが 「KO 」と表示したら、それはpush_swapが数字をソートしていない命令リストを作成したことを意味します。

```
checker_OSプログラムはイントラネットのプロジェクトのリソースにあります。このドキュメントのボーナス・パートにどのように動作するかの説明があります。
```

# Chapter VI

# Bonus part

This project leaves little room for adding extra features due to its simplicity. However, how about creating your own checker?

```
Thanks to the checker program, you will be able to check whether the list of instructions generated by the push_swap program actually sorts the stack properly.
```

このプロジェクトは、そのシンプルさゆえに、余分な機能を追加する余地をほとんど残していない。しかし、独自のチェッカーを作るのはどうだろう？

```
チェッカー・プログラムのおかげで、push_swapプログラムによって生成された命令リストが実際にスタックを正しくソートしているかどうかをチェックできるようになる。
```


### VI.1 The "checker" program

```
Program name checker
Turn in files *.h, *.c
Makefile bonus
Arguments stack A : A list of integers
External functs.
```
- read, write, malloc, free, exit
- ft_printf and any equivalent YOU coded

```
Libft authorized Yes
Description Execute the sorting instructions
```
- Write a program namedcheckerthat takes as an argument the stack A formatted as a list of integers. The first argument should be at the top of the stack (be careful about the order). If no argument is given, it stops and displays nothing.
- It will then wait and read instructions on the standard input, each instruction will be followed by ’\n’. Once all the instructions have been read, the program has to execute them on the stack received as an argument.


Push_swap Because Swap_push isn’t as natural

- If after executing those instructions, the stack A is actually sorted and the stack B  is empty, then the program must display"OK"followed by a ’\n’ on the standard output.
- In every other case, it must display"KO"followed by a ’\n’ on the standard output.
- In case of error, you must display"Error"followed by a ’\n’ on the **standard er-** **ror**. Errors include for example: some arguments are not integers, some arguments are bigger than an integer, there are duplicates, an instruction doesn’t exist and/or is incorrectly formatted.

```
プログラム名チェッカー
ファイル *.h, *.c を回す
Makefile ボーナス
引数 stack A ： 整数のリスト
外部関数
```
- read, write, malloc, free, exit
- ft_printf およびそれに相当する YOU コード化された関数

```
Libft 認証あり
説明 ソート命令の実行
```
- 整数のリストとしてフォーマットされたスタックを引数にとるcheckerという名前のプログラムを書きなさい。最初の引数はスタックの先頭でなければならない(順番に注意)。引数が与えられなければ、チェッカーは停止し、何も表示しない。
- その後、待機して標準入力の命令を読み、各命令の後に'˶n'が続く。すべての命令が読み込まれたら、プログラムは引数として受け取ったスタック上でそれらを実行しなければならない。


Swap_pushは自然ではないので、Push_swap。

- これらの命令を実行した後、スタックが実際にソートされ、スタッ クが空になったら、プログラムは 「OK 」の後に'˶n'を標準出力に表示しなけれ ばならない。
- それ以外の場合は、標準出力に 「KO 」に続いて'˶n'を表示しなければならない。
- エラーの場合は 「Error 」の後に'˶'を表示しなければなりません。エラーには、例えば、引数が整数でない、引数が整数より大きい、重複している、命令が存在しない、書式が正しくない、などがあります。

$>./checker 3 2 1 0
rra
pb
sa
rra
pa
OK
$>./checker 3 2 1 0
sa
rra
pb
KO
$>./checker 3 2 one 0
Error
$>./checker "" 1
Error
$>

```
You DO NOT have to reproduce the exact same behavior as the provided binary. It is mandatory to manage errors but it is up to you to decide how you want to parse the arguments.
```
```
The bonus part will only be assessed if the mandatory part is PERFECT. Perfect means the mandatory part has been integrally done and works without malfunctioning. If you have not passed ALL the mandatory requirements, your bonus part will not be evaluated at all.
```

```
提供されたバイナリとまったく同じ動作を再現する必要はありません。エラーを管理することは必須ですが、引数をどのように解析するかはあなた次第です。
```
```
ボーナスパートは、必須パートがパーフェクトである場合にのみ評価されます。パーフェクトとは、必須パートが統合的に行われ、誤動作することなく動作することを意味します。必須条件をすべてクリアしていない場合、ボーナスパートはまったく評価されません。
```

# Chapter VII

# Submission and peer-evaluation

Turn in your assignment in yourGitrepository as usual. Only the work inside your repository will be evaluated during the defense. Don’t hesitate to double check the names of your files to ensure they are correct.

As these assignments are not verified by a program, feel free to organize your files as you wish, as long as you turn in the mandatory files and comply with the requirements.

```
file.bfe:VABB7yO9xm7xWXROeASsmsgnY0o0sDMJev7zFHhwQS8mvM8V5xQQp
Lc6cDCFXDWTiFzZ2H9skYkiJ/DpQtnM/uZ
```

通常通り、Gitリポジトリに課題を提出してください。あなたのリポジトリ内の作業のみが、ディフェンス中に評価されます。ファイル名が正しいかどうか、ためらわずにダブルチェックしてください。

これらの課題はプログラムによって検証されないので、必須ファイルを提出し、要件を遵守している限り、自由にファイルを整理してください。

```
file.bfe:VABB7yO9xm7xWXROeASsmsgnY0o0sDMJev7zFHhwQS8mvM8V5xQQp
Lc6cDCFXDWTiFzZ2H9skYkiJ/DpQtnM/uZ
```

