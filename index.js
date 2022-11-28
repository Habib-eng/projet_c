let result = true;
ch = "ABAABA";
let i = 0;
while (result && i < ch.length / 2) {
  console.log(ch[i], ch[ch.length - i - 1]);
  i++;
  if (ch[i] != ch[ch.length - i - 1]) {
    break;
  }
}
