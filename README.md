# Push Swap

## プロジェクト概要

Push Swapは、限られた命令セットを使用して、2つのスタック上の整数をソートするアルゴリズムを実装するプロジェクトです。目標は、可能な限り少ない命令数で整数をソートすることです。

このプロジェクトでは、以下の2つのスタックを使用します：
- スタックA：初期の整数が格納される
- スタックB：ソート処理の補助として使用される

## 使用可能な命令

以下の命令を使用してスタックを操作します：

- `sa`: スタックAの先頭2つの要素を交換（swap a）
- `sb`: スタックBの先頭2つの要素を交換（swap b）
- `ss`: `sa`と`sb`を同時に実行
- `pa`: スタックBの先頭要素をスタックAの先頭に移動（push a）
- `pb`: スタックAの先頭要素をスタックBの先頭に移動（push b）
- `ra`: スタックAの全要素を上に1つシフト（先頭要素は最後に移動）（rotate a）
- `rb`: スタックBの全要素を上に1つシフト（rotate b）
- `rr`: `ra`と`rb`を同時に実行
- `rra`: スタックAの全要素を下に1つシフト（最後の要素が先頭に移動）（reverse rotate a）
- `rrb`: スタックBの全要素を下に1つシフト（reverse rotate b）
- `rrr`: `rra`と`rrb`を同時に実行

## 実装アルゴリズム

このプロジェクトでは、データサイズに応じて異なるソートアルゴリズムを実装しています：

1. **3つ以下の要素**：特定のパターンに基づく最適化されたソート
2. **5つ以下の要素**：最小値を見つけてスタックBに移動し、残りをソートした後に戻す方法
3. **中規模サイズ（〜100要素）**：チャンクソートアルゴリズム
   - 値の範囲をチャンクに分割
   - 各チャンクの要素をスタックBに移動
   - 最適な順序でスタックAに戻す
4. **大規模サイズ（〜500要素）**：改良版チャンクソートアルゴリズム
   - より多くのチャンクを使用
   - 回転操作の最適化

## コンパイル方法

以下のコマンドでプログラムをコンパイルします：

```bash
make
```

クリーンアップするには：

```bash
make clean    # オブジェクトファイルを削除
make fclean   # オブジェクトファイルと実行ファイルを削除
make re       # 再コンパイル
```

## 使用方法

### Push Swap

```bash
./push_swap [整数リスト]
```

例：
```bash
./push_swap 5 2 9 1 3
```

これにより、整数をソートするための命令リストが標準出力に表示されます。

### 命令数の確認

命令数を確認するには：

```bash
./push_swap [整数リスト] | wc -l
```

### テスト

プロジェクトにはテストスクリプトが含まれています：

```bash
bash push_swap_test.sh
```

このスクリプトは、様々なサイズの整数リストに対してプログラムをテストし、命令数を表示します。

## プロジェクト構成

- `push_swap.c`: メインプログラム
- `push_swap.h`: ヘッダーファイル
- `stack_operations.c`: スタック操作の実装
- `error_handling.c`: エラー処理
- `index_conversion.c`: インデックス変換
- `chunk_sort.c`: チャンクソートアルゴリズムの実装
- `Makefile`: コンパイル用Makefile

## 注意事項

- 入力された整数は、INT_MIN〜INT_MAXの範囲内である必要があります
- 重複する整数は許可されていません
- 不正な入力（数字以外の文字など）があった場合、"Error"を出力して終了します

## 性能目標

- 3要素：最大2命令
- 5要素：最大12命令
- 100要素：最大700命令
- 500要素：最大5500命令

---

## 以下人間が記述

- windsurf を使って push_swap を実装
- 人間は1行もコードを書かなかった
- コーディング規則は教えていないので、 `norminette` は通していないし、ヘッダーの使用も制限していない


## 結果

```sh
❯ python3 push_swap_tester.py
Test 120 cases: arg_length=5 range=(-2147483648, 2147483647)
........................................................................................................................
---- Result ----
max   : 10
median: 7
min   : 0
See result.log for details
❯ python3 push_swap_tester.py -l 100
Test 200 cases: arg_length=100 range=(-2147483648, 2147483647)
........................................................................................................................................................................................................
---- Result ----
max   : 699
median: 636
min   : 571
See result.log for details
❯ python3 push_swap_tester.py -l 200
Test 200 cases: arg_length=200 range=(-2147483648, 2147483647)
........................................................................................................................................................................................................
---- Result ----
max   : 1926
median: 1779
min   : 1668
See result.log for details
❯ python3 push_swap_tester.py -l 500
Test 200 cases: arg_length=500 range=(-2147483648, 2147483647)
........................................................................................................................................................................................................
---- Result ----
max   : 6368
median: 6161
min   : 5951
See result.log for details
❯ python3 push_swap_tester.py -l 1000
Test 200 cases: arg_length=1000 range=(-2147483648, 2147483647)
........................................................................................................................................................................................................
---- Result ----
max   : 16367
median: 15785
min   : 15082
See result.log for details
```