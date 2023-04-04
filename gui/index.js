const express = require('express');
const fs = require('fs');
const path = require('path');
const { exec } = require('child_process');
const mysql = require('mysql2');

const pool = mysql.createPool({
  database: 'compilers',
  password: 'root',
  user: 'root',
});

const db = pool.promise();

const app = express();

app.set('view engine', 'ejs');
app.set('views', 'views');

app.use(express.urlencoded({ extended: false }));

app.get('/', async (req, res, next) => {
  // db.execute('SELECT * FROM Employee').then(([data]) => {
  //   console.log('Test Query');
  //   console.log(data);
  // });
  res.render('index');
});

app.post('/parse', async (req, res, next) => {
  const query = req.body.query;
  fs.writeFileSync('parser/input.txt', query.trim() + '\n');
  const child = exec('parser/a.out');
  child.on('exit', () => {
    console.log('Query generated');
    const gen = fs.readFileSync('parser/output.txt', 'utf-8');
    console.log(gen.trim());
    const execer = gen.trim();
    db.execute(execer)
      .then(([data]) => {
        let rows = [];
        if (data.length > 0) {
          rows = Object.keys(data[0]);
        }
        return res.render('table', {
          input: query,
          output: execer,
          data,
          rows,
        });
      })
      .catch((e) => {
        console.log(e);
        return res.send('error');
      });
  });
});

app.listen(3000, () => {
  console.log('Server Started');
});
