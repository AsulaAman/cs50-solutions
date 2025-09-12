  document.addEventListener('DOMContentLoaded', function () {
      if (window.expensesData === undefined || window.expensesData.length === 0) {
        console.log("No data available for chart");
        return;
      }

      console.log("Expenses data:", window.expensesData);

      const ctx = document.getElementById('expensesChart').getContext('2d');

      new Chart(ctx, {
          type: 'bar',
          data: {
            labels: window.expensesData.map(row => row.category),
            datasets: [{
                label: 'Total Expenses by Category (£)',
                data: window.expensesData.map(row => row.amount),
                backgroundColor: 'rgba(75, 192, 192, 0.2)',
                borderColor: 'rgba(75, 192, 192, 1)',
                borderWidth: 1
            }]
        },
        options: {
          indexAxis: 'y',
          responsive: true,
          plugins: {
            legend: { display: true },
            title: {
              display: true,
              text: 'Expenses by Category'
            }
          },
          scales: {
            x: {
              beginAtZero: true
            }
          }
        }
      });
  });
