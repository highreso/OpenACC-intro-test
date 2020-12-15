# インスタンスへのNvidia HPC SDKセットアップ

## 概要
OpenACCをインスタンスに導入して、CやFortranで書かれたコードを簡単に並列化できるようにする。

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