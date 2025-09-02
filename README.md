# Minishell

42 İstanbul projesi kapsamında geliştirilmiş basit bir Unix shell uygulaması.

## Özellikler

- **Built-in komutlar**: `echo`, `cd`, `pwd`, `export`, `unset`, `env`, `exit`
- **Komut yürütme**: PATH'te bulunan harici komutlar
- **Pipe desteği**: `|` ile komut zincirlemesi
- **Yönlendirme**: `<`, `>`, `>>` operatörleri
- **Environment değişkenleri**: `$VAR` genişletmesi
- **Tırnak desteği**: Tek ve çift tırnak işleme
- **Sinyal yönetimi**: Ctrl-C, Ctrl-D, Ctrl-\ 

## Kurulum

```bash
git clone <repo-url>
cd minishell
make
```

## Kullanım

```bash
./minishell
```

## Gereksinimler

- GNU Readline kütüphanesi
- GCC derleyici
- Make

## Test

```bash
make run  # Valgrind ile çalıştır
```

## Proje Yapısı

- `core/` - Ana shell fonksiyonları
- `parser/` - Komut ayrıştırıcı
- `executor/` - Komut yürütücü
- `builtins/` - Yerleşik komutlar
- `utils/` - Yardımcı fonksiyonlar

---
*42 İstanbul - minishell projesi*
