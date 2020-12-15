# インスタンスへのNvidia HPC SDKセットアップ

## 概要
OpenACCをインスタンスに導入して、CやFortranで書かれたコードを簡単に並列化できるようにする。

## 検証環境
- *dl系インスタンスでの検証を推奨

## 導入
### NVIDIA HPC SDK
[NVIDIA HPC SDK](https://developer.nvidia.com/hpc-sdk)からダウンロードとインストールを行う。
- ダウンロード
```bash
sudo wget https://developer.download.nvidia.com/hpc-sdk/20.11/nvhpc-20-11_20.11_amd64.deb
sudo wget https://developer.download.nvidia.com/hpc-sdk/20.11/nvhpc-2020_20.11_amd64.deb 
sudo wget https://developer.download.nvidia.com/hpc-sdk/20.11/nvhpc-20-11-cuda-multi_20.11_amd64.deb
```

- インストール
```bash
sudo apt-get install ./nvhpc-20-11_20.11_amd64.deb ./nvhpc-2020_20.11_amd64.deb ./nvhpc-20-11-cuda-multi_20.11_amd64.deb
```

- パスを通す
```bash
export PATH="$PATH:/opt/nvidia/hpc_sdk/Linux_x86_64/20.11/compilers/bin"
```

- 確認
```bash
# もしかしたらgfortran導入しなきゃかも
nvfortran --version
```

## 動作確認
### Fortran編
[このコード](https://github.com/highreso/OpenACC-intro-test/blob/master/laplace2.f90)を`laplace2.f90`というファイル名で保存する。
- with OpenACC
```bash
nvfortran -acc -O2 -Minfo=accel laplace2.f90 -o laplace2_with_OpenACC
```
で実行コードが出力されるので`./laplace2_with_OpenACC`で実行する

- without OpenACC
```bash
nvfortran  laplace2.f90 -o laplace2_without_OpenACC
```
で実行コードが出力されるの`./laplace2_without_OpenACC`で実行できる

### C, C++編
- セットアップ
CやC++についてはgccのv9.1以上でデフォルトでOpenACCコンパイルが可能なため、必ずしもHPC SDKを導入する必要はない。
gccのバージョンアップのみで対応する場合、まず下記でヴァージョンアップとデフォルトのgccコマンドの9.3化を行う。
```bash
sudo apt install -y software-properties-common
sudo add-apt-repository ppa:ubuntu-toolchain-r/test

sudo apt install -y gcc-7 gcc-8 gcc-9 

sudo apt install -y gcc-offload-nvptx
sudo apt install -y gcc-9-offload-nvptx  # こっちでうまく行った
```
上記でgccのバージョンアップと9化がおこなわれる。

- Cをコンパイルして動作確認
[このコード](https://github.com/highreso/OpenACC-intro-test/blob/master/Leibniz_formula_for_pi.c)を`Leibniz_formula_for_pi.c`というファイル名で保存する。
```bash
gcc Leibniz_formula_for_pi.c -fopenacc  -foffload=nvptx-none -foffload="-O3" -O3
./a.out 32000000000
pi = 3.141592653557 (45.31 s)  # 出力値
```

### GPUやCPUのパフォーマンスをリアルタイム監視する
- GPU
`watch --interval 0.1 rocm-smi`
- CPU
`watch -n.1 "cat /proc/cpuinfo | grep \"^[c]pu MHz\""`