  document.addEventListener('DOMContentLoaded', function () {
    const dataObject = window.expensesData;


      const labels = Object.keys(dataObject);
      const data = Object.values(dataObject);

      const ctx = document.getElementById('expensesChart').getContext('2d');

      new Chart(ctx, {
          type: 'bar',
          data: {
            labels: labels,
            datasets: [{
                label: 'Total Expenses by Category (£)',
                data: data,
                backgroundColor: 'rgba(80, 188, 188, 0.2)',
                borderColor: 'rgba(75, 192, 192, 1)',
                borderWidth: 1,
                hoverBackgroundColor: 'rgba(75, 192, 192, 0.4)',
            }]
        },
        options: {
          indexAxis: 'y',
          responsive: true,
          maintainAspectRatio: false,
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
